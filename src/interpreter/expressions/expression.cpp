#include "interpreter/expressions/expression.hpp"

Expression::Expression(Expr *exprNode, std::shared_ptr<Storage> storage)
    : exprNode(exprNode), storage(std::move(storage)) {}

void Expression::execute() {
  switch (exprNode->kind) {
  case NodeType::AssignmentExpr:
    AssignmentExpression(dynamic_cast<AssignmentExpr *>(exprNode), storage)
        .execute();
    break;
  case NodeType::BinaryExpr:
    BinaryExpression(dynamic_cast<BinaryExpr *>(exprNode), storage).execute();
    break;

  default:
    throw std::runtime_error("Unknown expression type!");
    break;
  }
}