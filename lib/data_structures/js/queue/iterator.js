export class QueueIteratorReturnType {
    constructor(done = true, value) {
        this.done = done;
        if (!this.done) {
            this.value = value;
        }
    }
}

export default class QueueIterator {
    static ReturnType = QueueIteratorReturnType;

    _queue = null;
    _next = null;
    _state_id = null;

    constructor(queue, next) {
        this._next = next || queue?._head;
        this._queue = queue;
        this._state_id = queue?._state_id;
    }

    next() {
        const ret = new IteratorReturn(!!this._next, _next._elem);
        this._next = this._next._ptr;
        return ret;
    }

    done() {
        return !!this._next;
    }

    valid() {
        return this._state_id == this._queue._state_id;
    }

    [Symbol.iterator]() {
        return this;
    }
}
