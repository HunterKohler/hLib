class AbstractClass {
    constructor({ methods = [] }) {
        if (Object.getPrototypeOf(new.target) == AbstractClass) {
            throw new Error("Cannot instantiate abstract class");
        }

        let root = new.target;
        while (
            Object.getPrototypeOf((root = Object.getPrototypeOf(root))) !=
            AbstractClass
        ) {}

        methods = methods.filter((method) => this[method] != "function");
        if (methods.length) {
            throw new Error(
                'Subclass of abstract class "' +
                    root.name +
                    '" must implement methods: ' +
                    methods.map((method) => `"${method}"`).join(", ")
            );
        }
    }
}
