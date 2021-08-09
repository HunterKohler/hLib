import predicate from './predicate';

describe("toBeTrue Predicate", () => {
    test("return true when given true", () => {
        expect(predicate(true)).toBe(true);
    });

    test.each([
        [false], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("return false when given %s", value => {
        expect(predicate(value)).toBe(false);
    });
});