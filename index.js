const addon = require('./build/Release/sQeeZ-Interpreter-Node');
const interpreter = new addon.InterpreterNode(require);

console.log(addon.pingInterpreter());
console.log(interpreter.pingInstance());
console.log(addon.info());
console.log(interpreter.interpret('log("Hello, World!");', false));