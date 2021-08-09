export default class QueueNode {
    _elem = null;
    _ptr = null;

    constructor(elem, ptr) {
        this._elem = elem;
        this._ptr = ptr;
    }
}
