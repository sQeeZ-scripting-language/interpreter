#include "interpreter/interpreter.hpp"

Interpreter::Interpreter(std::unique_ptr<Program>&& ast) : ast(std::move(ast)) {}
