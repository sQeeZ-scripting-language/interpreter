#include "interpreter/interpreter.hpp"

Interpreter::Interpreter(std::unique_ptr<Program>&& ast) : ast(std::move(ast)) {}

void Interpreter::interpret(bool devMode) {
    for (const auto& statement : ast->body) {
        Statement(statement.get()).execute();
    }
}
