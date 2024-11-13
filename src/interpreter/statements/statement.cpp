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
  default:
    Expression(dynamic_cast<Expr *>(stmtNode), storage).execute();
    break;
  }
}