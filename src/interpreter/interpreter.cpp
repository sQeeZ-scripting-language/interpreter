#include "interpreter/interpreter.hpp"

Interpreter::Interpreter(std::unique_ptr<Program> &&ast)
    : ast(std::move(ast)) {}

void Interpreter::interpret(bool devMode) {
  std::shared_ptr<Storage> storage = std::make_shared<Storage>();

  try {
    for (const auto &statement : ast->body) {
      Statement(statement.get(), storage).execute();
    }
  } catch (const std::exception &e) {
    handleException(e);
  }
}

void Interpreter::handleException(const std::exception &e) {
  std::string exceptionType = typeid(e).name();

  std::cerr << "\033[1;30m\033[41m[sQeeZ]: "
            << "Exception of type: " << exceptionType
            << " - Message: " << e.what() << "\033[0m" << std::endl;
}
