/**
 * Unfinished, extremely fast 'env' script parser.
 */
class EnvParser {
    static parse(source) {
        const parser = new EnvParser(source);
        return parser.data;
    }

    data = {};
    offset = 0;
    line = 1;
    column = 1;
    source = null;

    constructor(source, defer) {
        this.source = source;
        if (typeof source != "string") {
            throw TypeError();
        }

        this.exec();
    }

    input() {
        return this.source[this.offset];
    }

    done() {
        return this.offset == this.source.length;
    }

    exec() {
        while (!this.done()) {
            if (/[A-Z_]/i.test(this.next())) {
                const name = this.getName(/=/);
                this.assert(/=/);
                this.next();
                this.data[name] = this.getValue();
            }

            this.nextLine();
        }
    }

    /**
     * @param {number} delta Length to move offset.
     */
    next(delta = 1) {
        if (this.offset + delta > this.source.length) {
            throw Error();
        }

        this.offset += delta;

        while (delta > 0) {
            if (this.input() == "\n") {
                this.line++;
                this.column = 1;
            } else {
                this.column++;
            }

            delta--;
        }
    }

    /**
     * @param {boolean} [comment=false]
     */
    nextLine(comment = false) {
        while (this.input() != "\n") {
            if (this.input() == "#") {
                comment = true;
            }

            if (!this.comment) {
                this.assert(/\s/);
            }

            this.next();
        }

        this.next();
    }

    /**
     * @param {RegExp} end Pattern to end search.
     */
    getName(end) {
        let name = "";

        this.assert(/[A-Z_]/i);
        while (!end.test(this.input())) {
            this.assert(/[A-Z0-9_]/i);
            name += this.input();
        }

        return name;
    }

    getValue() {
        let value = "";

        if(/['"]/.test(this.input())) {
            const end = this.input();
            this.next();

            while(this.input() != end) {
                if(this.input() == "$") {
                    this.next();
                    this.assert(/{/);
                    this.next();

                    const name = this.getName(/}/);

                    if (typeof this.data[name] == "undefined") {
                        throw new Error();
                    }

                    value += this.data[name];
                } else if(this.input() == "\\") {
                    this.next();
                    value += ESCAPE_MAP[this.input()] ?? this.input();
                } else {
                    value += this.input();
                }

                this.next();
            }

            return value;
        } else {
            let value = "";
            while(/\S/.test(this.input())) {
                value += this.input();
                this.next();
            }

            if(/^0b[0-1]+$/.test(value)) {
                return parseInt(value.substring(2), 2)
            } else if(/^0x[0-9A-F]+$/i.test(value)) {
                return parseInt(value.substring(2), 16)
            } else if(/^0[0-7]+$/.test(value)) {
                return parseInt(value, 8);
            } else if(/^[0-9]*\.[0-9]*$/.test(value) && value != ".") {
                return parseFloat(value);
            }

            this.next();
            return value;
        }
    }

    /**
     * @param {RexExp} pattern
     */
    assert(pattern) {
        if (!pattern.test(this.input())) {
            throw new TypeError();
        }
    }
}