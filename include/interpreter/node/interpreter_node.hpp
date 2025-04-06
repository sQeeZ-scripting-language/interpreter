#ifndef INTERPRETER_NODE_HPP
#define INTERPRETER_NODE_HPP

#include <napi.h>

#include <iostream>
#include <regex>

#include "interpreter/interpreter.hpp"

Napi::String pingInterpreter(const Napi::CallbackInfo &args);
Napi::String info(const Napi::CallbackInfo &args);

class InterpreterNode : public Napi::ObjectWrap<InterpreterNode> {
private:
  Napi::FunctionReference _require;
  Napi::Env _env = Napi::Env(nullptr);

public:
  explicit InterpreterNode(const Napi::CallbackInfo &args);

  Napi::String pingInstance(const Napi::CallbackInfo &args);
  void interpret(const Napi::CallbackInfo &args);

  static Napi::Function GetClass(Napi::Env);
};

#endif  // INTERPRETER_NODE_HPP