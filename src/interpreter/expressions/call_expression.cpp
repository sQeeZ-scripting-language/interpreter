#include "interpreter/expressions/call_expression.hpp"

CallExpression::CallExpression(
    CallExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper CallExpression::execute() {
    // expressionNode->caller;
    if (expressionNode->caller == nullptr) {
        // function call
    } else {
        // method call
    }
    expressionNode->args;
    expressionNode->method;
}

Storage::DataWrapper CallExpression::functionCall() {
    throw std::runtime_error("Function call not implemented!");
}

Storage::DataWrapper CallExpression::methodCall() {
    throw std::runtime_error("Method call not implemented!");
}
