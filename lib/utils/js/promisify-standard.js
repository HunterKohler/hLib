// Copyright 2020-2021 John Hunter Kohler. All rights reserved.

// TODO

/**
 * A proposed standard 'Well-known Symbol' for denoting the proper method of
 * 'promisifying' some function.
 *
 * ##  Motivation
 *
 * ### Legacy Libraries
 * The symbol presents a standard pattern for 'porting' libraries or old code
 * which depends heavily on asynchronous methods through callbacks and hooks.
 * Though not technically 'legacy', this port would represent a *modernization*
 * of some api. Let the cultural and functional popularity of native
 * 'async/await', and 'promises' be self-evident. One may even argue that
 * such libraries are in fact legacy if they are being used to such a degree
 * that support, interest, or *non-trivial* developments have stopped.
 * Overhauling library api's certainly seems a daunting task at the momeny.
 */

Object.defineProperty(Symbol, "promisify", {
    value: Symbol("Symbol.promisify")
});

/**
 * The global 'promisify' symbol.
 *
 * @constant
 */
export const promisify = Symbol.promisify;

export default promisify;
