#include "interpreter/interpreter.hpp"

Interpreter::Interpreter(std::unique_ptr<Program> &&ast)
    : ast(std::move(ast)) {}

void Interpreter::interpret(bool devMode) {
  std::vector<std::shared_ptr<Storage>> storage = {std::make_shared<Storage>()};

  try {
    for (const auto &statement : ast->body) {
      Statement(statement.get(), storage).execute();
    }
  } catch (const std::exception &e) {
    handleException(e);
  }
}


