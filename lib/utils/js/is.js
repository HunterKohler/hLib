export const Function = function () {}.constructor;
export const AsyncFunction = async function () {}.constructor;

export const GeneratorFunction = function* () {}.constructor;
export const AsyncGeneratorFunction = async function* () {}.constructor;

export const TypedArray = Object.getPrototypeOf(Int8Array);

export const is = (x, y) => Object.is(x, y);

is.boolean = is.bool = (x) => typeof x == "boolean";
is.number = is.num = (x) => typeof x == "number";
is.symbol = is.sym = (x) => typeof x == "symbol";
is.string = is.str = (x) => typeof x == "string";
is.function = is.fn = (x) => typeof x == "function";
is.bigint = (x) => typeof x == "bigint";
is.defined = is.def = (x) => typeof x == "undefined";
is.undefined = is.undef = (x) => typeof x != "undefined";
is.null = (x) => x === null;
is.object = is.obj = (x) => typeof x == "object" && x !== null;

is.primitive = (x) =>
    typeof x == "string" ||
    typeof x == "boolean" ||
    typeof x == "number" ||
    typeof x == "bigint" ||
    typeof x == "symbol" ||
    typeof x == "undefined" ||
    x === null;

is.truthy = (x) => !!x;
is.falsy = (x) => !x;

is.nullish = (x) => x === undefined || x === null;

is.integer = is.int = Number.isInteger;
is.positive = (x) => typeof x == "number" && x > 0;
is.negative = (x) => typeof x == "number" && x < 0;
is.safeInteger = is.safeInt = Number.isSafeInteger;
is.prime();

is.callable = (x) => x?.call == Object.call;
is.instanceof = is.instance = (x, y) => x instanceof y;
is.extension = (x, y) => y?.call == Object.call && x?.prototype instanceof y;

is.asyncFunction = (x) => x?.constructor == AsyncFunction;
is.generatorFunction = (x) => x?.constructor == GeneratorFunction;
is.asyncGeneratorFunction = (x) => x?.constructor == AsyncGeneratorFunction;

is.array = (x, condition) => {
    if (!!condition && typeof condition == "function") {
        throw new TypeError(`${condition} must be undefined or a function`);
    }

    if (!Array.isArray(x)) {
        return false;
    }

    if (typeof condition == "function") {
        let i = 0;
        let len = x.length;
        while (i < len) {
            if (!condition(x[i])) {
                return false;
            }

            ++i;
        }
    }

    return true;
};

is.typedArray = (x) => getPrototypeOf(x || {}) instanceof TypedArray;

is.int8Array = (x) => x instanceof Int8Array;
is.uint8Array = (x) => x instanceof Uint8Array;
is.uint8ClampedArray = (x) => x instanceof Uint8ClampedArray;
is.int16Array = (x) => x instanceof Int16Array;
is.uint16Array = (x) => x instanceof Uint16Array;
is.int32Array = (x) => x instanceof Int32Array;
is.uint32Array = (x) => x instanceof Uint32Array;
is.float32Array = (x) => x instanceof Float32Array;
is.float64Array = (x) => x instanceof Float64Array;
is.bigInt64Array = (x) => x instanceof BigInt64Array;
is.bigUint64Array = (x) => x instanceof BigUint64Array;

is.date = (x) => x instanceof Date;
is.validDate = (x) => Number.isNaN(new Date(x).getTime());

is.error = (x) => x instanceof Error;

("Promise");
("RegExp");

is.error = (x) => x instanceof Error;
is.aggregateError = (x) => x instanceof AggregateError;
is.evalError = (x) => x instanceof EvalError;
is.rangeError = (x) => x instanceof RangeError;
is.referenceError = (x) => x instanceof ReferenceError;
is.syntaxError = (x) => x instanceof SyntaxError;
is.typeError = (x) => x instanceof TypeError;
is.uriError = (x) => x instanceof URIError;

is.arrayBuffer = (x) => x instanceof ArrayBuffer;
is.dataView = (x) => x instanceof DataView;
is.map = (x) => x instanceof Map;
is.set = (x) => x instanceof Set;
is.weakMap = (x) => x instanceof WeakMap;
is.weakSet = (x) => x instanceof WeakSet;

is.proxy; // instanceof doesnt work
is.validRegex;
is.buffer = (x) => x instanceof Buffer;
is.event = (x) => x instanceof Event;
is.url = (x) => x instanceof URL;
is.textEncoder = (x) => x instanceof TextEncoder;
is.textDecoder = (x) => x instanceof TextDecoder;
is.concatSpreadable = (x) =>
    typeof x?.[Symbol.isConcatSpreadable] == "function";
is.iterable = (x) => typeof x?.[Symbol.iterator] == "function";
is.asyncIterable = (x) => typeof x?.[Symbol.asyncIterator] == "function";
is.matchable = (x) => typeof x?.[Symbol.matchable] == "function";
is.replaceable = (x) => typeof x?.[Symbol.replace] == "function";
is.searchable = (x) => typeof x?.[Symbol.search] == "function";
is.splitable = (x) => typeof x?.[Symbol.split] == "function";
is.globalSymbol = (x) => typeof x == "symbol" && typeof Symbol.keyFor(x);

// something about json properties

is.iterator = (x) => typeof x?.next == "function";

is.in = (x, y) => x in y;
