import toBeNullish from "./";

expect.extend({ toBeNullish });

describe(".toBeNullish", () => {
    test.each([
        [undefined], [null]
    ])("pass when given %s", value => {
        expect(value).toBeNullish();
    });

    test.each([
        [false], [0], [1], [[]], [{}], [NaN], [""]
    ])("fail when given %s", value => {
        expect(() => expect(value).toBeNullish()).toThrowErrorMatchingSnapshot();
    });
});

describe(".not.toBeNullish", () => {
    test.each([
        [undefined], [null]
    ])("fail when given %s", value => {
        expect(() => expect(value).not.toBeNullish()).toThrowErrorMatchingSnapshot();
    });

    test.each([
        [false], [0], [1], [[]], [{}], [NaN], [""]
    ])("pass when given %s", value => {
        expect(value).not.toBeNullish()
    });
});
