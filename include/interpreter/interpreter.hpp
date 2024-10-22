#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "interpreter/statements/statement.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

class Interpreter {
  std::unique_ptr<Program> ast;

public:
  Interpreter(std::unique_ptr<Program> &&ast);
  void interpret(bool devMode);

private:
  void handleException(const std::exception &e);
};

#endif // INTERPRETER_HPP