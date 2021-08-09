import QueueNode from "./node.js";
import QueueIterator from "./iterator.js";

export default class Queue {
    static Node = QueueNode;
    static Iterator = QueueIterator;

    _tail = null;
    _head = null;
    _size = null;
    _state_id = 0;

    constructor(iterable) {
        this.pushAll(iterable);
    }

    push(elem) {
        this._state_id++;
        if (this._head) {
            this._head = new Queue.Node(elem, this._head);
        } else {
            this._head = new Queue.Node(elem);
            this._tail = new Queue.Node(elem);
        }
    }

    pushAll(iterable) {
        for (const elem of iterable) this.push(elem);
        return this;
    }

    front() {
        return this._head._elem;
    }

    pop() {
        this._state_id++;
        if (this._head) {
            const elem = this._head._elem;
            this._head = this._head._ptr;
            return elem;
        } else {
            throw new Error("Pulled pop on empty queue");
        }
    }

    size() {
        return this._size;
    }

    empty() {
        return this._size == 0;
    }

    begin() {
        return new Queue.Iterator(this);
    }

    end() {
        return new Queue.Iterator(this, new Queue.Node());
    }

    [Symbol.iterator]() {
        return new Queue.Iterator(this);
    }
}
