#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt *stmtNode,
                     std::vector<std::shared_ptr<Storage>> storage,
                     std::shared_ptr<Logs> logs)
    : stmtNode(stmtNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper Statement::execute() {
  switch (stmtNode->kind) {
  case NodeType::FunctionDeclaration:
    DeclarationStatement(dynamic_cast<FunctionDeclaration *>(stmtNode), storage,
                         logs)
        .execute();
    break;
  case NodeType::VarDeclaration:
    DeclarationStatement(dynamic_cast<VarDeclaration *>(stmtNode), storage,
                         logs)
        .execute();
    break;
  case NodeType::ConditionalStmt:
    return ConditionalStatement(dynamic_cast<ConditionalStmt *>(stmtNode),
                                storage, logs)
        .execute();
  case NodeType::WhileStmt:
    return LoopStatement(dynamic_cast<WhileStmt *>(stmtNode), storage, logs)
        .execute();
  case NodeType::DoWhileStmt:
    return LoopStatement(dynamic_cast<DoWhileStmt *>(stmtNode), storage, logs)
        .execute();
  case NodeType::ForStmt:
    return LoopStatement(dynamic_cast<ForStmt *>(stmtNode), storage, logs)
        .execute();
  case NodeType::ForInStmt:
    return LoopStatement(dynamic_cast<ForInStmt *>(stmtNode), storage, logs)
        .execute();
  case NodeType::ForOfStmt:
    return LoopStatement(dynamic_cast<ForOfStmt *>(stmtNode), storage, logs)
        .execute();
  case NodeType::LogStmt:
    LogStatement(dynamic_cast<LogStmt *>(stmtNode), storage, logs).execute();
    break;
  case NodeType::ReturnStmt:
    return ReturnStatement(dynamic_cast<ReturnStmt *>(stmtNode), storage, logs)
        .execute();
    break;
  default:
    return Expression(dynamic_cast<Expr *>(stmtNode), storage, logs).execute();
    break;
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}