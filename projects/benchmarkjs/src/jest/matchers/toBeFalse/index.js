import { matcherHint, printReceived, printExpected } from "jest-matcher-utils";
import predicate from "./predicate";

const passMessage = recieved => () =>
    matcherHint(".not.toBeFalse", "recieved", "") 
    + "\n\n"
    + "Expected value to not be false, recieved:\n"
    + `    ${printReceived(recieved)}`;

const failMessage = recieved => () =>
    matcherHint(".toBeFalse", "recieved", "")
    + "\n\n"
    + "Expected value to be false:\n"
    + `    ${printExpected(false)}\n`
    + "Recieved:\n"
    + `    ${printReceived(recieved)}`;

export default function toBeFalse(recieved) {
    const pass = predicate(recieved);
    return { pass, message: pass
        ? passMessage(recieved)
        : failMessage(recieved)
    };
}