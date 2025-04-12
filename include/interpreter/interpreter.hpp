#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "interpreter/logs.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

class Interpreter {
  std::unique_ptr<Program> ast;

public:
  Interpreter(std::unique_ptr<Program> &&ast);
  std::shared_ptr<Logs> interpret(bool devMode);
};

#endif // INTERPRETER_HPP