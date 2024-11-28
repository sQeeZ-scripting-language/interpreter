#include "interpreter/statements/loop_statement.hpp"

LoopStatement::LoopStatement(WhileStmt *loopNode,
                             std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(DoWhileStmt *loopNode,
                             std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForStmt *loopNode,
                             std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForInStmt *loopNode,
                             std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForOfStmt *loopNode,
                             std::shared_ptr<Storage> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

void LoopStatement::execute() {
  if (std::holds_alternative<WhileStmt *>(loopNode)) {
    executeWhileLoop();
  } else if (std::holds_alternative<DoWhileStmt *>(loopNode)) {
    executeDoWhileLoop();
  } else if (std::holds_alternative<ForStmt *>(loopNode)) {
    executeForLoop();
  } else if (std::holds_alternative<ForInStmt *>(loopNode)) {
    executeForInLoop();
  } else if (std::holds_alternative<ForOfStmt *>(loopNode)) {
    executeForOfLoop();
  }
}

void LoopStatement::executeWhileLoop() {
  auto whileLoop = std::get<WhileStmt *>(loopNode);
  while (checkTrueishness(whileLoop->condition, storage)) {
    for (const auto &stmt : whileLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
  }
}

void LoopStatement::executeDoWhileLoop() {
  auto doWhileLoop = std::get<DoWhileStmt *>(loopNode);
  do {
    for (const auto &stmt : doWhileLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
  } while (checkTrueishness(doWhileLoop->condition, storage));
}

void LoopStatement::executeForLoop() {
  auto forLoop = std::get<ForStmt *>(loopNode);
  while (checkTrueishness(forLoop->condition, storage)) {
    for (const auto &stmt : forLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
    if (forLoop->increment) {
      Statement(forLoop->increment.get(), storage).execute();
    }
  }
}

void LoopStatement::executeForInLoop() {}

void LoopStatement::executeForOfLoop() {}
