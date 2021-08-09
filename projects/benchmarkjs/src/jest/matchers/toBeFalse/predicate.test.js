import predicate from "./predicate";

describe("toBeFalse Predicate", () =>  {
    test("return true when given false", () => {
        expect(predicate(false)).toBe(true);
    });

    test.each([
        [true], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("return false when given %s", value => {
        expect(predicate(value)).toBe(false);
    })
})