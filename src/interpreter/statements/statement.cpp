#include "interpreter/statements/statement.hpp"

Statement::Statement(Stmt* stmtNode) : stmtNode(stmtNode) {}

void Statement::execute() {
    switch (stmtNode->kind) {
    case NodeType::LogStmt:
        LogStatement(dynamic_cast<LogStmt*>(stmtNode)).execute();
        break;
    
    default:
        throw std::runtime_error("Unknown statement type");
        break;
    }
}