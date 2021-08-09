// TODO conform to A+ standard on promises
// TODO benchmark (library)
// TODO do benchmarks
// TODO find out benchmark of instanceof
// TODO lookup SameValueZero, implement eq, eqeq, eqeqeq

/**
 * @typicalname _
 * @module functional
 */

/**
 * @template T
 * @param {Iterable<T>} object
 * @return {Iterator<T>}
 */
export function iterator(object) {
    return object[Symbol.iterator]();
}

/**
 * @template T
 * @param {AsyncIterable<T>} object
 * @returns {AsyncIterator<T>}
 */
export function asyncIterator(object) {
    return object[Symbol.asyncIterator]();
}

/**
 * @param {any} a
 * @param {any} b
 * @returns {boolean}
 */
export function eq(a, b) {
    return a == b;
}

/**
 * @template T
 * @param {T} object
 * @returns {T}
 */
export function identity(object) {
    return object;
}

/**
 * @param {any[]} object
 * @returns {boolean}
 */
export function isArray(object) {
    return Array.isArray(object);
}

/**
 * @template T
 * @param {T[]} array
 * @param {number} index
 * @returns {T}
 */
export function at(array, index) {
    const { length } = array;

    if (!length) {
        return undefined;
    }

    return array[index < 0 ? length - (index % length) : index % length];
}

export function* range(start = 0, end, step = 1) {
    if (end === undefined) {
        end = start;
        start = 0;
    }

    if (step > 0) {
        while (start < end) {
            yield start;
            start += step;
        }
    } else {
        while (start > end) {
            yield start;
            start += step;
        }
    }
}

/**
 * @param {object} object
 * @returns {string[]}
 */
export function keys(object) {
    return Object.keys(object);
}

/**
 * @param {object} object
 * @returns {any[]}
 */
export function values(object) {
    return Object.values(object);
}

/**
 * @typedef {Array} Entry
 * @property {string} 0
 * @property {any} 1
 */

/**
 * @param {object} object
 * @returns {Entry[]}
 */
export function entries(object) {
    return Object.entries(object);
}

/**
 * @typedef {string|symbol|number} KeyType
 */

/**
 * @typedef {string} PathString
 */

/**
 * @param {object} object
 * @param {Array<KeyType[] | PathString>} paths
 * @returns {object}
 */
export function pick(object, paths) {}

/**
 * @param {object} object
 * @param {Array<KeyType[] | PathString>} paths
 * @returns {PathString}
 */
export function omit(object, paths) {}

/**
 * @param {KeyType[] | PathString} path
 * @returns {KeyType[]}
 */
export function pathArray(path) {}
