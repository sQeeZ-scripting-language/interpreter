#include "interpreter/expressions/expression.hpp"

Expression::Expression(Expr *exprNode, std::shared_ptr<Storage> storage)
    : exprNode(exprNode), storage(std::move(storage)) {}

Storage::DataWrapper Expression::execute() {
  switch (exprNode->kind) {
  case NodeType::AssignmentExpr:
    AssignmentExpression(dynamic_cast<AssignmentExpr *>(exprNode), storage)
        .execute();
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
  case NodeType::BinaryExpr:
    return BinaryExpression(dynamic_cast<BinaryExpr *>(exprNode), storage).execute();
  default:
    return LiteralExpression(exprNode, storage).execute();
  }
}