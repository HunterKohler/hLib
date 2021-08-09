// Copyright 2020-2021 John Hunter Kohler. All rights reserved.

// TODO

export class Mixer {
    _base;
    _mixins;

    get base() {
        return this._base;
    }

    constructor(base) {
        this._base = base;
        this._mixins = [];
    }

    with(...cls) {
        if (!cls.length) {
            throw TypeError();
        }

        for (const i of cls) {
            this._mixins.push(i);
        }

        Object.apply(this.prototype, ...cls);
    }

    _rebuild() {
        this.prototype = this._base;
        Object.apply(this.prototype, ...this._mixins);
    }
}

export default Mixer;
