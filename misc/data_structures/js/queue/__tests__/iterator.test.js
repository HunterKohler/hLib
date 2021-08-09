import QueueIterator, { QueueIteratorReturnType } from "../iterator";

describe("QueueIteratorReturnType", () => {
    describe("constructor", () => {
        test("no value property when done", () => {
            const returntype = new QueueIteratorReturnType(true, "value");
            expect(returntype).toBeInstanceOf(QueueIteratorReturnType);
            expect(returntype.done).toBeTrue();
            expect(returntype).not.toHaveProperty("value");
        });

        test("value assigned when not done", () => {
            const returntype = new QueueIteratorReturnType(false, "value");
            expect(returntype).toBeInstanceOf(QueueIteratorReturnType);
            expect(returntype.done).toBeFalse();
            expect(returntype.value).toEqual("value");
        });
    });

    test("constructor", () => {
        let returntype = new QueueIteratorReturnType(false, "value");
        expect(returntype).toBeInstanceOf(QueueIteratorReturnType);
        expect(returntype.done).toBeFalse();
        expect(returntype.value).toEqual("value");
    });
});

describe("QueueIterator", () => {
    describe("constructor", () => {
        test("full constructor", () => {
            const queue = { _state_id: "STATE_ID" };
            const iterator = new QueueIterator(queue, "NEXT");
            expect(iterator).toBeInstanceOf(QueueIterator);
            expect(iterator._queue).toBe(queue);
            expect(iterator._next).toEqual("NEXT");
            expect(iterator._state_id).toEqual("STATE_ID");
        });

        test("empty constructor", () => {
            expect(new QueueIterator()).toBeInstanceOf(QueueIterator);
        });

        test("'next' parameter default", () => {
            const queue = { _head: "HEAD", _state_id: "STATE_ID" };
            const iterator = new QueueIterator(queue);
            expect(iterator).toBeInstanceOf(QueueIterator);
            expect(iterator._queue).toBe(queue);
            expect(iterator._next).toEqual("HEAD");
            expect(iterator._state_id).toBe("STATE_ID");
        });
    });

    describe("statics", () => {
        test("ReturnType is QueueIteratorReturnType", () => {
            expect(QueueIterator.ReturnType).toBe(QueueIteratorReturnType);
        });
    });

    describe("methods", () => {
        test.todo("done");
        test.todo("next");

        describe("valid", () => {
            const queue = { _state_id: 0 };
            const iterator = new QueueIterator(queue);

            test("true after creation", () => {
                expect(iterator.valid()).toBeTrue();
            });

            test("false after _queue._state_id increment", () => {
                queue._state_id++;
                expect(iterator.valid()).toBeFalse();
            });
        });

        describe("[Symbol.iterator]", () => {
            test("returns this", () => {
                const iterator = new QueueIterator();
                expect(iterator[Symbol.iterator]()).toBe(iterator);
            });
        });
    });
});
