import QueueNode from "../node.js";

describe("QueueNode", () => {
    test("constructor", () => {
        let qnode = new QueueNode("element", new QueueNode());
        expect(qnode).toBeInstanceOf(QueueNode);
        expect(qnode._ptr).toBeInstanceOf(QueueNode);
        expect(qnode._elem).toEqual("element");
    });

    test("empty constructor", () => {
        let qnode = new QueueNode();
        expect(qnode).toBeInstanceOf(QueueNode);
        expect(qnode._ptr).toBeUndefined();
        expect(qnode._elem).toBeUndefined();
    });
});
