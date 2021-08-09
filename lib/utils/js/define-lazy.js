// Copyright 2020-2021 John Hunter Kohler. All rights reserved.

/**
 * Private module level memory for lazy evaluation cache.
 *
 * @internal
 * @type {WeakMap}
 */
const wm = new WeakMap();

/**
 * Defines getter that returns the value of the lazily evaluated callback.
 * Trivially, the getter caches the callback return value.
 *
 * The bound object of the getter determines the lifeespan of its cached value.
 *
 * @param {object} object
 * @param {string} name property name to define
 * @param {function} cb callback to run for lazy evaluation
 * @param {...any} args arguments to pass to callback
 */
export function defineLazy(object, name, cb, ...args) {
    Object.defineProperty(object, name, {
        get() {
            if (wm.has(this)) {
                return wm.get(this);
            }

            wm.set(this, cb(...args));
            return wm.get(this);
        },
        enumerable: true,
        configurable: true
    });
}

export default defineLazy;
