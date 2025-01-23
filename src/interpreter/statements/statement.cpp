#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt *stmtNode,
                     std::vector<std::shared_ptr<Storage>> storage)
    : stmtNode(stmtNode), storage(std::move(storage)) {}

void Statement::execute() {
  switch (stmtNode->kind) {
  case NodeType::FunctionDeclaration:
    DeclarationStatement(dynamic_cast<FunctionDeclaration *>(stmtNode), storage)
        .execute();
    break;
  case NodeType::VarDeclaration:
    DeclarationStatement(dynamic_cast<VarDeclaration *>(stmtNode), storage)
        .execute();
    break;
  case NodeType::ConditionalStmt:
    ConditionalStatement(dynamic_cast<ConditionalStmt *>(stmtNode), storage)
        .execute();
    break;
  case NodeType::WhileStmt:
    LoopStatement(dynamic_cast<WhileStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::DoWhileStmt:
    LoopStatement(dynamic_cast<DoWhileStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::ForStmt:
    LoopStatement(dynamic_cast<ForStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::ForInStmt:
    LoopStatement(dynamic_cast<ForInStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::ForOfStmt:
    LoopStatement(dynamic_cast<ForOfStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::LogStmt:
    LogStatement(dynamic_cast<LogStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::ReturnStmt:
    ReturnStatement(dynamic_cast<ReturnStmt *>(stmtNode), storage).execute();
    break;
  default:
    Expression(dynamic_cast<Expr *>(stmtNode), storage).execute();
    break;
  }
}