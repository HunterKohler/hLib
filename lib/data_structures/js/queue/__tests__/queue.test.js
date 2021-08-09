import Queue from "../queue.js";
import QueueNode from "../node.js";
import QueueIterator from "../iterator";

describe("Queue", () => {
    describe("statics", () => {
        test("Queue.Node is QueueNode", () => {
            expect(Queue.Node).toBe(QueueNode);
        });

        test("Queue.Iterator is QueueIterator", () => {
            expect(Queue.Iterator).toBe(QueueIterator);
        });
    });

    describe("constructor", () => {
        // test("empty constructor", () => {
        //     const queue = new Queue();
        //     expect(queue).toBeInstanceOf(Queue);
        // });
        // test("construct from iterable", () => {
        //     expect()
        // });
    });

    describe("methods", () => {});
});
