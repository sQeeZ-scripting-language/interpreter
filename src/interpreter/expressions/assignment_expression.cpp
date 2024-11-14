#include "interpreter/expressions/assignment_expression.hpp"

AssignmentExpression::AssignmentExpression(AssignmentExpr *expressionNode,
                                           std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

void AssignmentExpression::execute() {
  if (auto assignee =
          dynamic_cast<Identifier *>(expressionNode->assignee.get())) {
    if (expressionNode->value) {
      storage->updateValue(assignee->identifier.value,
                           static_cast<Expr *>(expressionNode->value.get()));
    }
  } else {
    throw std::logic_error("Assignee must be an identifier");
  }
}