- [Jest Setup & Matchers](#jest-setup--matchers)
  - [Matchers](#matchers)
    - [Predicate Test](#predicate-test)
      - [Example](#example)
    - [Index Test](#index-test)
      - [Example](#example-1)

# Jest Setup & Matchers

## Matchers

Each matcher must have subdirectory in [matchers](./matchers) named, in camel case, after said matcher, containing:

```text
.
├── index.js
├── index.test.js
├── predicate.js
└── predicate.test.js
```

### Predicate Test

The predicate test, in `./matchers/*/predicate.test.js` must be wrapped in a
describe block of name "`* Predicate`". Import statement of predicate should be
to `./predicate.js`, by default named as `predicate`.

#### Example

```javascript
import predicate from "./predicate.js";

describe("toBe Predicate", () => {
    // ...
});
```

### Index Test

The index test, in `./matchers/*/index.test.js` must contain two describe blocks
of name "`.*`" and "`.not.*`". Import statements should be to the index by path
"`./`", not "`./index.js`", by the default, named "`*`";

#### Example

``` javascript
import toBe from "./";

describe(".toBe", () => {
    // ...
});

describe(".not.toBe", () => {
    // ...
});
```
