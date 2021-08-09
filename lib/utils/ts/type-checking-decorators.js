import { inspect } from "util";

function log(...x) {
    x.forEach((v) => console.log(inspect(v, true, null, true)));
}

const metadata = Symbol("metadata");
const typechecker = Symbol("typechecker");

Function.prototype[metadata] = {
    types: {
        arguments: [],
        returns: undefined
    }
};

export function copyFunctionMetadata(target, source) {
    target[metadata] = source[metadata];
    return Object.defineProperty(target, "name", { name: source.name });
}

export function signature(...types) {
    if (types.length == 0) {
        throw new TypeError("No signature types provided");
    }

    types.forEach((type) => {
        if (typeof type != "string" && typeof type != "function") {
            throw TypeError("Type checks must use type string or constructor");
        }
    });

    return function decorator(object, name, descriptor) {
        function wrapper(...args) {
            if (args.length != types.length) {
                throw new TypeError(
                    `Function ${name} expects ${types.length} arguments`
                );
            }

            types.forEach((type, index) => {
                if (
                    (typeof type == "string" && typeof args[index] != type) ||
                    (typeof type == "function" &&
                        !(args[index] instanceof type))
                ) {
                    throw new TypeError(
                        `Function ${name} expects ${type} at arg ${index}`
                    );
                }
            });

            descriptor.value(...args);
        }

        return {
            ...descriptor,
            value: Object.defineProperty(wrapper, "name", { value: name })
        };
    };
}

function isType(object, typename) {
    return (
        (typename instanceof Type && typename[typecheck](object)) ||
        (typeof typename == "string" && typeof object == typename) ||
        (typeof typename == "function" && object instanceof typename)
    );
}

export function typecheck(object, name, descriptor) {
    const { types } = descriptor.value[metadata];

    function wrapper(...args) {
        types.arguments.forEach((typename, index) => {
            if (typename && !isType(args[index], typename)) {
                throw new TypeError(
                    `${name} expected type '${typename}' at argument ${index}`
                );
            }
        });

        const ret = descriptor.value(...args);

        if (types.returns && !isType(ret, types.returns)) {
            throw new TypeError(
                `${name} expected return type '${types.returns}'`
            );
        }

        return ret;
    }

    copyFunctionMetadata(wrapper, descriptor.value);

    return {
        ...descriptor,
        value: wrapper
    };
}

export function type(typename) {
    return function (object, name, index) {
        object[name][metadata].types.arguments[index] = typename;
    };
}

export const string = type("string");
export const undef = type("undefined");
export const object = type("object");
export const symbol = type("symbol");
export const bigint = type("bigint");

class Type {
    constructor(check) {
        this[typecheck] = check;
    }
};

export function array(typename) {

}
