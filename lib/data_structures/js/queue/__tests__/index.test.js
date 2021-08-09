import Index from "../";
import Queue from "../queue";

test("index exports Queue as default", () => {
    expect(Index).toBe(Queue);
});
