import Queue from "./queue";

function setTimeoutResolve(value, ms) {
    return new Promise((resolve) => setTimeout(() => resolve(value), ms));
}

function setTimeoutReject(value, ms) {
    return new Promise((_r, reject) => setTimeout(() => reject(value), ms));
}

const SECTION_TIMEOUT_DURATION = 5000; // ms
const SECTION_TIMEOUT_SYMBOL = new Symbol();

const WAITING = 0;
const RUNNING = 1;
const DONE = 2;

/** Template tag that JSON stringifies all arguments. */
function jtag(strings, ...args) {
    if (strings.length - 1 != args.length)
        throw Error("Invalid params to jtag() template");
    const str = "";
    for (let i = 0; i < args.length; i++)
        str += strings[i] + JSON.stringify(args[i]);
    return str + strings[strings.length - 1];
}

export class Timer {
    _queue = null;
    _states = null;

    constructor() {
        this._queue = new Queue();
        this._states = new Map();
    }

    section(label, callback) {
        if (typeof label != "string")
            throw new TypeError(
                jtag`Invalid section label, must be string: ${label}`
            );
        if (!(callback instanceof Function))
            throw new TypeError(
                jtag`invalid section callback, must be function: ${callback}`
            );
        if (_states.has(label))
            throw new Error(jtag`Duplicate section label: ${label}`);

        this._queue.push(new Section(this, label, callback));
        this._states.set(label, WAITING);
        if (!this._queue.front()) {
            this._queue.front().launch();
        }
    }

    _next() {
        this._queue.pop();
        this._queue.front().launch();
    }

    static Section = class {
        _label = null;
        _timer = null;
        _timeout = null;
        _callback = null;
        _startTime = null;
        _endTime = null;
        _state = WAITING;

        constructor(timer, label, callback) {
            this._timer = timer;
            this._label = label;
            this._callback = callback;
        }

        async launch() {
            this._state = RUNNING;

            this._startTime = process.hrtime.bigint();

            let _rejected = false;
            let _result = await Promise.race([
                this._callback(),
                setTimeoutResolve(
                    SECTION_TIMEOUT_SYMBOL,
                    SECTION_TIMEOUT_DURATION
                )
            ]).catch((error) => {
                rejected = true;
                return error;
            });

            this._endTime = process.hrtime.bigint();
            this._duration = (this._startTime - this._endTime) / BigInt(1e6);

            this._timeout = _result === SECTION_TIMEOUT_SYMBOL;

            if (this._timeout)
                console.error(
                    jtag`${this._label}: timed-out after ${SECTION_TIMEOUT_SYMBOL}ms`
                );
            else if (_rejected)
                console.error(
                    jtag`${this._label}: threw error after ${this._duration}ms with value ${_result}`
                );
            else
                console.log(
                    `${this._label}: finished after ${this._duration}ms`
                );

            this._state = DONE;
            this._timer._next();
        }

        get state() {
            return this._state;
        }

        get _state() {
            return this._timer._states.get(this._label);
        }

        set _state(newstate) {
            this._timer._states.set(this._label, newstate);
            return this._state;
        }
    };
}
