#include "interpreter/statements/loop_statement.hpp"

LoopStatement::LoopStatement(WhileStmt *loopNode,
                             std::vector<std::shared_ptr<Storage>> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(DoWhileStmt *loopNode,
                             std::vector<std::shared_ptr<Storage>> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForStmt *loopNode,
                             std::vector<std::shared_ptr<Storage>> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForInStmt *loopNode,
                             std::vector<std::shared_ptr<Storage>> storage)
    : loopNode(loopNode), storage(std::move(storage)) {}

LoopStatement::LoopStatement(ForOfStmt *loopNode,
                             std::vector<std::shared_ptr<Storage>> storage)
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
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : whileLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  }
}

void LoopStatement::executeDoWhileLoop() {
  auto doWhileLoop = std::get<DoWhileStmt *>(loopNode);
  do {
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : doWhileLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  } while (checkTrueishness(doWhileLoop->condition, storage));
}

void LoopStatement::executeForLoop() {
  auto forLoop = std::get<ForStmt *>(loopNode);
  storage.push_back(std::make_shared<Storage>());
  forLoop->iterator ? Statement(forLoop->iterator.get(), storage).execute()
                    : void();
  while (checkTrueishness(forLoop->condition, storage)) {
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : forLoop->body) {
      Statement(stmt.get(), storage).execute();
    }
    if (forLoop->increment) {
      Statement(forLoop->increment.get(), storage).execute();
    }
    storage.pop_back();
  }
  storage.pop_back();
}

void LoopStatement::executeForOfLoop() {
  auto forOfLoop = std::get<ForOfStmt *>(loopNode);
}

void LoopStatement::executeForInLoop() {
  auto forInLoop = std::get<ForInStmt *>(loopNode);
}
