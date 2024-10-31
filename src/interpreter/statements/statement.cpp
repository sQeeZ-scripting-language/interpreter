#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt *stmtNode, std::shared_ptr<Storage> storage) : stmtNode(stmtNode), storage(std::move(storage)) {}

void Statement::execute() {
  switch (stmtNode->kind) {
  case NodeType::LogStmt:
    LogStatement(dynamic_cast<LogStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::FunctionDeclaration:
    DeclarationStatement(dynamic_cast<FunctionDeclaration *>(stmtNode), storage).execute();
    break;
  case NodeType::VarDeclaration:
    DeclarationStatement(dynamic_cast<VarDeclaration *>(stmtNode), storage).execute();
    break;

  case NodeType::AssignmentExpr:
  case NodeType::CompoundAssignmentExpr:
  case NodeType::TernaryExpr:
  case NodeType::BinaryExpr:
  case NodeType::UnaryExpr:
  case NodeType::CallExpr:
  case NodeType::MemberExpr:
  case NodeType::Property:
  case NodeType::ObjectLiteral:
  case NodeType::ArrayLiteral:
  case NodeType::Identifier:
  case NodeType::NullLiteral:
  case NodeType::IntegerLiteral:
  case NodeType::DoubleLiteral:
  case NodeType::BooleanLiteral:
  case NodeType::CharLiteral:
  case NodeType::StringLiteral:
  case NodeType::HexCodeLiteral:
  case NodeType::ShortOperationLiteral:
  case NodeType::ShortSingleExpressionLiteral:
  case NodeType::ShortDoubleExpressionLiteral:
    Expression(dynamic_cast<Expr *>(stmtNode), storage).execute();
    break;

  default:
    throw std::runtime_error("Unknown statement type!");
    break;
  }
}