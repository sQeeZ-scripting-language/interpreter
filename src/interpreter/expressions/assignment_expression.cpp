#include "interpreter/expressions/assignment_expression.hpp"

AssignmentExpression::AssignmentExpression(AssignmentExpr *expressionNode, std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

void AssignmentExpression::execute() {
    if (auto assignee = dynamic_cast<Identifier*>(expressionNode->assignee.get())) {
        auto value = expressionNode->value.get();
        // TODO: update storage
    } else {
        throw std::logic_error("Assignee must be an identifier");
    }
}