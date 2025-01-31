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

Storage::DataWrapper LoopStatement::execute() {
  if (std::holds_alternative<WhileStmt *>(loopNode)) {
    return executeWhileLoop();
  } else if (std::holds_alternative<DoWhileStmt *>(loopNode)) {
    return executeDoWhileLoop();
  } else if (std::holds_alternative<ForStmt *>(loopNode)) {
    return executeForLoop();
  } else if (std::holds_alternative<ForInStmt *>(loopNode)) {
    return executeForInLoop();
  } else if (std::holds_alternative<ForOfStmt *>(loopNode)) {
    return executeForOfLoop();
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}

Storage::DataWrapper LoopStatement::executeWhileLoop() {
  auto whileLoop = std::get<WhileStmt *>(loopNode);
  while (checkTrueishnessOfExpression(whileLoop->condition, storage)) {
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : whileLoop->body) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage)
            .execute();
      }
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}

Storage::DataWrapper LoopStatement::executeDoWhileLoop() {
  auto doWhileLoop = std::get<DoWhileStmt *>(loopNode);
  do {
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : doWhileLoop->body) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage)
            .execute();
      }
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  } while (checkTrueishnessOfExpression(doWhileLoop->condition, storage));
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}

Storage::DataWrapper LoopStatement::executeForLoop() {
  auto forLoop = std::get<ForStmt *>(loopNode);
  storage.push_back(std::make_shared<Storage>());
  if (forLoop->iterator) {
    Statement(forLoop->iterator.get(), storage).execute();
  }
  while (checkTrueishnessOfExpression(forLoop->condition, storage)) {
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : forLoop->body) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage)
            .execute();
      }
      Statement(stmt.get(), storage).execute();
    }
    if (forLoop->increment) {
      Statement(forLoop->increment.get(), storage).execute();
    }
    storage.pop_back();
  }
  storage.pop_back();
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}

Storage::DataWrapper LoopStatement::executeForOfLoop() {
  auto forOfLoop = std::get<ForOfStmt *>(loopNode);
  storage.push_back(std::make_shared<Storage>());
  std::vector<std::string> keys =
      DeclarationStatement(
          dynamic_cast<VarDeclaration *>(forOfLoop->iterator.get()), storage)
          .declareLoopVariables();
  Storage::DataWrapper iterable =
      Expression(forOfLoop->iterable.get(), storage).execute();
  if (iterable.dataType != Storage::DataType::ARRAY) {
    throw std::runtime_error("Iterable is not an array!");
  }
  for (const auto &data : *iterable.data._array) {
    storage.back()->updateValue(keys.front(), data);
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : forOfLoop->body) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage)
            .execute();
      }
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}

Storage::DataWrapper LoopStatement::executeForInLoop() {
  auto forInLoop = std::get<ForInStmt *>(loopNode);
  storage.push_back(std::make_shared<Storage>());
  std::vector<std::string> keys =
      DeclarationStatement(
          dynamic_cast<VarDeclaration *>(forInLoop->iterator.get()), storage)
          .declareLoopVariables();
  Storage::DataWrapper iterable =
      Expression(forInLoop->iterable.get(), storage).execute();
  if (iterable.dataType != Storage::DataType::OBJECT) {
    throw std::runtime_error("Iterable is not an object!");
  }
  for (const auto &data : *iterable.data._object) {
    storage.back()->updateValue(
        keys.front(), Storage::DataWrapper(Storage::WrapperType::VALUE,
                                           Storage::DataType::STRING,
                                           new std::string(data.first)));
    if (keys.size() > 1) {
      storage.back()->updateValue(keys.at(1), data.second);
    }
    storage.push_back(std::make_shared<Storage>());
    for (const auto &stmt : forInLoop->body) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage)
            .execute();
      }
      Statement(stmt.get(), storage).execute();
    }
    storage.pop_back();
  }
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}
