import { matcherHint, printReceived, printExpected } from "jest-matcher-utils";
import predicate from "./predicate";

const passMessage = recieved => () =>
    matcherHint(".not.toBeNullish", "recieved", "") 
    + "\n\n"
    + `Expected value to not be nullish, recieved:`
    + `    ${printReceived(recieved)}`;

const failMessage = recieved => () =>
    matcherHint(".toBeNullish", "recieved", "")
    + "\n\n"
    + "Expected value to be nullish, recieved:"
    + `    ${printReceived(recieved)}`

export default function toBeNullish(recieved) {
    const pass = predicate(recieved);
    return { pass, message: pass
        ? passMessage(recieved)
        : failMessage(recieved)
    };
}
