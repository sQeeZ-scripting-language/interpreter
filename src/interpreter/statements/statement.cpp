#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt *stmtNode,
                     std::vector<std::shared_ptr<Storage>> storage)
    : stmtNode(stmtNode), storage(std::move(storage)) {}

Storage::DataWrapper Statement::execute() {
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
    return ConditionalStatement(dynamic_cast<ConditionalStmt *>(stmtNode),
                                storage)
        .execute();
  case NodeType::WhileStmt:
    return LoopStatement(dynamic_cast<WhileStmt *>(stmtNode), storage)
        .execute();
  case NodeType::DoWhileStmt:
    return LoopStatement(dynamic_cast<DoWhileStmt *>(stmtNode), storage)
        .execute();
  case NodeType::ForStmt:
    return LoopStatement(dynamic_cast<ForStmt *>(stmtNode), storage).execute();
  case NodeType::ForInStmt:
    return LoopStatement(dynamic_cast<ForInStmt *>(stmtNode), storage)
        .execute();
  case NodeType::ForOfStmt:
    return LoopStatement(dynamic_cast<ForOfStmt *>(stmtNode), storage)
        .execute();
  case NodeType::LogStmt:
    LogStatement(dynamic_cast<LogStmt *>(stmtNode), storage).execute();
    break;
  case NodeType::ReturnStmt:
    return ReturnStatement(dynamic_cast<ReturnStmt *>(stmtNode), storage)
        .execute();
    break;
  default:
    return Expression(dynamic_cast<Expr *>(stmtNode), storage).execute();
    break;
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}