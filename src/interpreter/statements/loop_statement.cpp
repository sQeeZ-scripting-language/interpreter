#include "interpreter/statements/loop_statement.hpp"

LoopStatement::LoopStatement(WhileStmt *loopNode, std::shared_ptr<Storage> storage)
    : declarationNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(DoWhileStmt *loopNode, std::shared_ptr<Storage> storage)
    : declarationNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForStmt *loopNode, std::shared_ptr<Storage> storage)
    : declarationNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForInStmt *loopNode, std::shared_ptr<Storage> storage)
    : declarationNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForOfStmt *loopNode, std::shared_ptr<Storage> storage)
    : declarationNode(loopNode), storage(std::move(storage)) {}

void LoopStatement::execute() {

}