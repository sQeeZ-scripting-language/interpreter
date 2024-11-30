#include "interpreter/expressions/assignment_expression.hpp"

AssignmentExpression::AssignmentExpression(Expr *expressionNode,
                                           std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

void AssignmentExpression::execute() {
  if (auto expr = dynamic_cast<AssignmentExpr *>(expressionNode)) {
    if (auto assignee = dynamic_cast<Identifier *>(expr->assignee.get())) {
      if (expr->value) {
        int keyIndex = storageKeyIndex(storage, assignee->identifier.value);
        if (keyIndex == -1) {
          throw std::logic_error("Variable not declared.");
        }
        storage[keyIndex]->updateValue(
            assignee->identifier.value,
            Expression(dynamic_cast<Expr *>(expr->value.get()), storage)
                .execute());
      }
    } else {
      throw std::logic_error("Assignee must be an identifier");
    }
  } else if (auto expr =
                 dynamic_cast<CompoundAssignmentExpr *>(expressionNode)) {
    if (expr->operator_.tag == Token::TypeTag::OPERATOR) {
      if (auto assignee = dynamic_cast<Identifier *>(expr->assignee.get())) {
        Storage::DataWrapper value =
            Expression(dynamic_cast<Expr *>(expr->value.get()), storage)
                .execute();
        int keyIndex = storageKeyIndex(storage, assignee->identifier.value);
        if (keyIndex == -1) {
          throw std::logic_error("Variable not declared.");
        }
        Storage::DataWrapper assigneeValue =
            storage[keyIndex]->getEntry(assignee->identifier.value);
        switch (expr->operator_.type.operatorToken) {
        case OperatorToken::ADDITION_ASSIGNMENT:
          storage[keyIndex]->updateValue(
              assignee->identifier.value,
              BinaryExpression::addition(assigneeValue, value));
          break;
        case OperatorToken::SUBTRACTION_ASSIGNMENT:
          storage[keyIndex]->updateValue(
              assignee->identifier.value,
              BinaryExpression::subtraction(assigneeValue, value));
          break;
        case OperatorToken::MULTIPLICATION_ASSIGNMENT:
          storage[keyIndex]->updateValue(
              assignee->identifier.value,
              BinaryExpression::multiplication(assigneeValue, value));
          break;
        case OperatorToken::DIVISION_ASSIGNMENT:
          storage[keyIndex]->updateValue(
              assignee->identifier.value,
              BinaryExpression::division(assigneeValue, value));
          break;
        case OperatorToken::MODULUS_ASSIGNMENT:
          storage[keyIndex]->updateValue(assignee->identifier.value,
                               BinaryExpression::modulus(assigneeValue, value));
          break;
        default:
          throw std::logic_error("Unsupported compound assignment operator.");
        }
      } else {
        throw std::logic_error("Assignee must be an identifier");
      }
    } else {
      throw std::logic_error("Unsupported compound assignment expression.");
    }
  } else {
    throw std::logic_error("Unsupported assignment expression.");
  }
}