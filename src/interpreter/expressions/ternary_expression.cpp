#include "interpreter/expressions/ternary_expression.hpp"

TernaryExpression::TernaryExpression(
    TernaryExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper TernaryExpression::execute() {
  Storage::DataWrapper condition =
      Expression(dynamic_cast<Expr *>(expressionNode->condition.get()), storage)
          .execute();
  if (checkTrueishness(condition, storage)) {
    return Expression(dynamic_cast<Expr *>(expressionNode->trueExpr.get()),
                      storage)
        .execute();
  } else {
    return Expression(dynamic_cast<Expr *>(expressionNode->falseExpr.get()),
                      storage)
        .execute();
  }
}