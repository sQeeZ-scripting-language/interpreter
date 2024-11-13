#include "interpreter/expressions/assignment_expression.hpp"

AssignmentExpression::AssignmentExpression(AssignmentExpr *expressionNode, std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

void AssignmentExpression::execute() {
    if (auto assignee = dynamic_cast<Identifier*>(expressionNode->assignee.get())) {
        if (expressionNode->value) {
            if (auto expr = dynamic_cast<IntegerLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, expr->value);
            } else if (auto expr = dynamic_cast<DoubleLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, expr->value);
            } else if (auto expr = dynamic_cast<BooleanLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, expr->value);
            } else if (auto expr = dynamic_cast<CharLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, expr->value);
            } else if (auto expr = dynamic_cast<StringLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, new std::string(expr->value));
            } else if (auto expr = dynamic_cast<HexCodeLiteral*>(expressionNode->value.get())) {
                storage->updateValue(assignee->identifier.value, new std::string(expr->value));
            } else {
                throw std::invalid_argument("Unknown literal type!");
            }
        }
    } else {
        throw std::logic_error("Assignee must be an identifier");
    }
}