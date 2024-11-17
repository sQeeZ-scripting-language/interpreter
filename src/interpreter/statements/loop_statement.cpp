#include "interpreter/statements/loop_statement.hpp"

LoopStatement::LoopStatement(WhileStmt *loopNode, std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(DoWhileStmt *loopNode, std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForStmt *loopNode, std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForInStmt *loopNode, std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForOfStmt *loopNode, std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

void LoopStatement::execute() {
    if (std::holds_alternative<WhileStmt *>(loopNode)) {

    } else if (std::holds_alternative<DoWhileStmt *>(loopNode)) {

    } else if (std::holds_alternative<ForStmt *>(loopNode)) {

    } else if (std::holds_alternative<ForInStmt *>(loopNode)) {

    } else if (std::holds_alternative<ForOfStmt *>(loopNode)) {

    }
}

void executeWhileLoop() {
    
}

void executeDoWhileLoop() {
    
}

void executeForLoop() {
    
}

void executeForInLoop() {
    
}

void executeForOfLoop() {
    
}
