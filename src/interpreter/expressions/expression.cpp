#include "interpreter/expressions/expression.hpp"

Expression::Expression(Expr *exprNode,
                       std::vector<std::shared_ptr<Storage>> storage)
    : exprNode(exprNode), storage(std::move(storage)) {}

Storage::DataWrapper Expression::execute() {
  switch (exprNode->kind) {
  case NodeType::AssignmentExpr:
  case NodeType::CompoundAssignmentExpr:
    AssignmentExpression(exprNode, storage).execute();
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::_NULL, 0);
  case NodeType::TernaryExpr:
    return TernaryExpression(dynamic_cast<TernaryExpr *>(exprNode), storage)
        .execute();
  case NodeType::BinaryExpr:
    return BinaryExpression(dynamic_cast<BinaryExpr *>(exprNode), storage)
        .execute();
  case NodeType::UnaryExpr:
    return UnaryExpression(dynamic_cast<UnaryExpr *>(exprNode), storage)
        .execute();
  case NodeType::CallExpr:
    return CallExpression(dynamic_cast<CallExpr *>(exprNode), storage)
        .execute();
  case NodeType::MemberExpr:
    return MemberExpression(dynamic_cast<MemberExpr *>(exprNode), storage)
        .execute();
  case NodeType::CallbackFunctionExpr:
    return CallbackFunctionExpression(
               dynamic_cast<CallbackFunctionExpr *>(exprNode), storage)
        .execute();
  case NodeType::ShortOperationExpr:
    return ShortOperationExpression(
               dynamic_cast<ShortOperationExpr *>(exprNode), storage)
        .execute();
  default:
    return LiteralExpression(exprNode, storage).execute();
  }
}