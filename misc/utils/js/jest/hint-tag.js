import { EXPECTED_COLOR, RECEIVED_COLOR, DIM_COLOR } from "jest-matcher-utils";

/**
 * @module jest-hint-tag
 */

/**
 * Pattern of javascript variable names.
 *
 * @internal
 * @constant
 * @type {RegExp}
 */
const RE_VARNAME = /^[a-zA-Z_$][a-zA-Z0-9_$]*$/;

/**
 * Jest matcher hint utility to color and format said hint.
 *
 * @param {{ isNot: boolean }} context Calling functon's context, intended to
 *     be the `this` object of a Jest matcher's scope.
 * @returns {hintTagTemplate} Templating function that will take a parsable
 *     string and turn it into the matcher's hint.
 */
export default function hintTag({ isNot }) {
    /**
     * Can be used as a template function, or one taking just a string. They
     * produce the same result, as all but the first string of a template
     * literal param set is ignored.
     *
     * @param {(string|string[])} str Template literal string array (first
     *     array member will be used), or the string to parse directly.
     * @returns {string} The calling matcher's hint.
     */
    export function hintTagTemplate(str) {
        const err = new Error(`Invalid matcher hint: ${str}`);

        if (Array.isArray(str)) {
            [str] = str;
        }

        if (typeof str != "string") {
            throw err;
        }

        let [func, args, empty, none] = str.split(/[()]/);

        func = func.trim();
        empty = empty.trim();

        if (
            !RE_VARNAME.test(func) ||
            args == undefined ||
            empty.trim() != "" ||
            none != undefined
        ) {
            throw err;
        }

        args = args.split(",").map((x) => x.trim());

        if (!args.length || args.some((arg) => !RE_VARNAME.test(arg))) {
            throw err;
        }

        return (
            DIM_COLOR(`expected(`) +
            RECEIVED_COLOR(args[0]) +
            DIM_COLOR(")") +
            (isNot ? DIM_COLOR(".") + "not" : "") +
            DIM_COLOR(".") +
            func +
            DIM_COLOR("(") +
            EXPECTED_COLOR(args.slice(1).join(", ")) +
            DIM_COLOR(")")
        );
    }

    return hintTagTemplate;
}
