#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

class Interpreter {
    std::unique_ptr<Program> ast;
    
public:
    Interpreter(std::unique_ptr<Program>&& ast) : ast(std::move(ast)) {}
};


#endif