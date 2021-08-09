import predicate from "./predicate";

describe("toBeNullish Predicate", () =>  {
    test.each([
        [undefined], [null]
    ])("return true when given %s", value => {
        expect(predicate(value)).toBeTrue();
    });

    test.each([
        [false], [0], [1], [[]], [{}], [NaN], [""] 
    ])("return false when given %s", value => {
        expect(predicate(value)).toBeFalse()
    })
});
