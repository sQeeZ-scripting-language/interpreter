#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt *stmtNode, std::shared_ptr<Storage> storage) : stmtNode(stmtNode), storage(std::move(storage)) {}

void Statement::execute() {
  switch (stmtNode->kind) {
  case NodeType::LogStmt:
    LogStatement(dynamic_cast<LogStmt *>(stmtNode)).execute();
    break;

  default:
    throw std::runtime_error("Unknown statement type!");
    break;
  }
}