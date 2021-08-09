const nullptr = Symbol("nullptr");

class LRUCache {
    _head = null;
    _tail = null;
    _cache = null;
    _added = null;
    _timeout = null;

    constructor({ maxAge, maxSize, dealloc }) {
        this.maxAge = maxAge;
        this.maxSize = maxSize;
        this.dealloc = dealloc;

        this._cache = new Map();
        this._added = new Map();

        this._head = this._tail = nullptr;

        this.set = this.set.bind(this);
        this.get = this.get.bind(this);
        this.has = this.has.bind(this);
        this.remove = this.remove.bind(this);
        this._timeoutHandler = this._timeoutHandler.bind(this);
    }

    _timeoutHandler() {
        const now = Date.now();

        while (
            this._head != nullptr &&
            now - this._added.get(this._head.value) >= this.maxAge
        ) {
            if (this.dealloc) {
                this._cache.remove(this._head.value);
                this.dealloc(this._head.value);
            }

            this._head = this._head.next;
        }

        if (this._head != this._tail) {
            this._timeout = setTimeout(
                this._timeoutHandler,
                this.maxAge - (now - this._added.get(this._head.value))
            );
        } else {
            this._timeout = null;
        }
    }

    set(key, value) {
        this._cache(key, value);
        this._added(key, Date.now());

        if (!this._timeout) {
            this._timeout = setTimeout(this._timeoutHandler, this.maxAge);
        }

    }

    get(key) {
        if (!this.has(key)) {
            throw new Error("Key not found");
        }

        return this._cache(key);
    }

    has(key) {
        this._cache.has(key);
    }

    remove(key) {
        const value = this._cache.get(key);
        this._cache.remove(key);
        return value;
    }

    get size() {
        this._cache.size;
    }
}
