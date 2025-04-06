#include "interpreter/node/interpreter_node.hpp"

InterpreterNode::InterpreterNode(const Napi::CallbackInfo &args) : ObjectWrap(args) {
  this->_env = args.Env();
  if (args.Length() < 1 || !args[0].IsFunction()) {
    Napi::TypeError::New(this->_env, "Function expected").ThrowAsJavaScriptException();
  }
  Napi::Function require = args[0].As<Napi::Function>();
  std::regex self_regex("^function require\\(path\\)", std::regex_constants::ECMAScript | std::regex_constants::icase);
  if (!std::regex_search(require.ToString().Utf8Value().c_str(), self_regex)) {
    Napi::TypeError::New(this->_env, "{require} Function expected").ThrowAsJavaScriptException();
  }
  this->_require = Persistent(require);
}

Napi::String InterpreterNode::pingInstance(const Napi::CallbackInfo &args) {
  return Napi::String::New(this->_env, "Node instance of the sQeeZ-Interpreter is working!");
}

void InterpreterNode::interpret(const Napi::CallbackInfo &args) {
  if (args.Length() < 1 || !args[0].IsString()) {
    Napi::TypeError::New(this->_env, "Code expected!").ThrowAsJavaScriptException();
  }
  Napi::Env env = args.Env();
  auto code = args[0].As<Napi::String>().Utf8Value();
  bool devMode = false;
  if (args.Length() >= 2 && args[1].IsBoolean()) {
    devMode = args[1].As<Napi::Boolean>().Value();
  }
  Lexer lexer(code);
  std::vector<Token> tokens = lexer.tokenize(devMode);
  Parser parser(tokens);
  std::unique_ptr<Program> program = parser.parse(devMode);
  if (program == nullptr) {
    Napi::TypeError::New(env, "Failed to parse the code!").ThrowAsJavaScriptException();
  }
  Interpreter interpreter(std::move(program));
  interpreter.interpret(devMode);
}

Napi::Function InterpreterNode::GetClass(Napi::Env env) {
  return DefineClass(
      env, "InterpreterNode",
      {InterpreterNode::InstanceMethod("pingInstance", reinterpret_cast<InstanceMethodCallback>(&InterpreterNode::pingInstance)),
       InterpreterNode::InstanceMethod("interpret", reinterpret_cast<InstanceMethodCallback>(&InterpreterNode::interpret))});
}

Napi::String pingInterpreter(const Napi::CallbackInfo &args) {
  Napi::Env env = args.Env();
  return Napi::String::New(env, "Node API for Interpreter is working!");
}

Napi::String info(const Napi::CallbackInfo &args) {
  Napi::Env env = args.Env();
  std::string info = R"(
    sQeeZ-Interpreter Node API Information:

    - Command Methods:
      1. info: Provides this API information.
      2. pingInterpreter: Pings the module to check if it's responsive.

    - Instance Methods:
      1. ping: Pings the interpreter instance.
      2. parse: Processes and interprets a provided code snippet.
    )";
  return Napi::String::New(env, info);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "pingInterpreter"), Napi::Function::New(env, pingInterpreter));
  exports.Set(Napi::String::New(env, "info"), Napi::Function::New(env, info));
  Napi::String name = Napi::String::New(env, "InterpreterNode");
  exports.Set(name, InterpreterNode::GetClass(env));
  return exports;
}

NODE_API_MODULE(interpreter, Init)