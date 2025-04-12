#include "interpreter/expressions/ternary_expression.hpp"

TernaryExpression::TernaryExpression(
    TernaryExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage,
    std::shared_ptr<Logs> logs)
    : expressionNode(expressionNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper TernaryExpression::execute() {
  Storage::DataWrapper condition =
      Expression(dynamic_cast<Expr *>(expressionNode->condition.get()), storage,
                 logs)
          .execute();
  if (checkTrueishness(condition, storage)) {
    return Expression(dynamic_cast<Expr *>(expressionNode->trueExpr.get()),
                      storage, logs)
        .execute();
  } else {
    return Expression(dynamic_cast<Expr *>(expressionNode->falseExpr.get()),
                      storage, logs)
        .execute();
  }
}