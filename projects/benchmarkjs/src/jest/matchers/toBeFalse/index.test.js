import toBeFalse from "./";

expect.extend({ toBeFalse });

describe(".toBeFalse", () => {
    test("pass when given false", () => {
        expect(false).toBeFalse();
    });

    test.each([
        [true], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("fail when given %s", value => {
        expect(() => expect(value).toBeFalse()).toThrowErrorMatchingSnapshot();
    });
})

describe(".not.toBeFalse", () => {
    test("fail when given false", () => {
        expect(() => expect(false).not.toBeFalse()).toThrowErrorMatchingSnapshot();
    });

    test.each([
        [true], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("pass when given %s", value => {
        expect(value).not.toBeFalse();
    });
});