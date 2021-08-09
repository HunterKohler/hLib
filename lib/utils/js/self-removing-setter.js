/**
 * Assigns a setter to an object which will ignore non-promise values, and
 * upon recieving a promise, will redefine itself to remove setter logic,
 * and redefine the property to the resolved value of the promise.
 *
 *
 * @template ValueType
 * @param {object} object Object to assign property.
 * @param {string|symbol|number} property Property name.
 * @param {object} options
 * @param {boolean} [options.enumerable=true] Final `enumerable` attribute.
 * @param {boolean} [options.configurable=true] Final `configurable` attribute.
 * @param {boolean} [options.writable=true] Final `writtable` attribute.
 * @param {(value: ValueType) => boolean} [options.isPromise=Promise[Symbol.hasInstance]]
 *     Used to identity wether a value is a promise. Useful if you would like
 *     to use this for thenable extraneous lib promises, etc.
 * @returns {object} `object` parameter
 */
function assignPropertyResolver(
    object,
    property,
    {
        enumerable = true,
        configurable = true,
        writable = true,
        isPromise = Promise[Symbol.hasInstance]
    }
) {
    return Object.defineProperty(object, property, {
        configurable: true,
        enumerable: false,

        get() {
            throw new Error("Property uninitialized");
        },

        /** @param {ValueType} value */
        set(value) {
            if (isPromise(value)) {
                // Disable setter logic to disallow multiple promises to be
                // assigned.
                Object.defineProperty(this, property, {
                    ...Object.getOwnPropertyDescriptor(this, property),
                    set(v) {}
                });

                value.then((resolvedValue) =>
                    Object.defineProperty(this, property, {
                        enumerable,
                        configurable,
                        writable,
                        value: resolvedValue
                    })
                );
            }
        }
    });
}
