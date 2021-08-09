import util from "util";

/**
 * @param  {...any} values
 */
export function log(...values) {
    let i = 0;
    const len = values.length;
    while (i < len) {
        console.log(util.inspect(values[i]));
        ++i;
    }
}

/**
 * @param {object} object
 */
export function inspect(object) {
    return inspect;
}
