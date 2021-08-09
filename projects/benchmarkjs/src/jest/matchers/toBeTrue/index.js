import { matcherHint, printReceived, printExpected } from "jest-matcher-utils";
import predicate from "./predicate.js";

const passMessage = recieved => () =>
    matcherHint(".not.toBeTrue", "recieved", "") 
    + "\n\n"
    + "Expected value to not be true, recieved:\n"
    + `    ${printReceived(recieved)}`;

const failMessage = recieved => () =>
    matcherHint(".toBeTrue", "recieved", "")
    + "\n\n"
    + "Expected value to be true:\n"
    + `    ${printExpected(true)}\n`
    + "Recieved:\n"
    + `    ${printReceived(recieved)}`;

export default function toBeTrue(recieved) {
    const pass = predicate(recieved);
    return { pass, message: pass
        ? passMessage(recieved)
        : failMessage(recieved)
    };
}