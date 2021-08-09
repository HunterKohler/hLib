import toBeTrue from "./";

expect.extend({ toBeTrue });

describe(".toBeTrue", () => {
    test("pass when given true", () => {
        expect(true).toBeTrue();
    })

    test.each([
        [false], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("fail when given %s", value => {
        expect(() => expect(value).toBeTrue()).toThrowErrorMatchingSnapshot();
    });
});

describe(".not.toBeTrue", () => {
    test("fail when given true", () => {
        expect(() => expect(true).not.toBeTrue()).toThrowErrorMatchingSnapshot();
    });

    test.each([
        [false], [""], [0], [1], [{}], [[]], [undefined], [null], [NaN]
    ])("pass when given %s", value => {
        expect(() => expect(value).not.toBeTrue());
    })
});