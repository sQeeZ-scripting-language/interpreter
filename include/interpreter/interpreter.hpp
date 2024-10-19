#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "interpreter/statements/statement.hpp"

class Interpreter {
    std::unique_ptr<Program> ast;

public:
    Interpreter(std::unique_ptr<Program>&& ast);
    void interpret(bool devMode);
};


#endif