#include "interpreter/interpreter.hpp"

Interpreter::Interpreter(std::unique_ptr<Program> &&ast)
    : ast(std::move(ast)) {}

std::shared_ptr<Logs> Interpreter::interpret(bool devMode) {
  std::vector<std::shared_ptr<Storage>> storage = {std::make_shared<Storage>()};
  std::shared_ptr<Logs> logs = std::make_shared<Logs>();

  try {
    for (const auto &statement : ast->body) {
      Statement(statement.get(), storage, logs).execute();
    }
  } catch (const std::exception &e) {
    handleException(e);
  }
  return logs;
}
