#include "interpreter/statements/conditional_statement.hpp"

ConditionalStatement::ConditionalStatement(
    ConditionalStmt *conditionalNode,
    std::vector<std::shared_ptr<Storage>> storage, std::shared_ptr<Logs> logs)
    : conditionalNode(conditionalNode), storage(std::move(storage)),
      logs(logs) {}

Storage::DataWrapper ConditionalStatement::execute() {
  bool executed = false;
  storage.push_back(std::make_shared<Storage>());
  if (checkTrueishnessOfExpression(conditionalNode->ifClause.first, storage,
                                   logs)) {
    for (const auto &stmt : conditionalNode->ifClause.second) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage,
                               logs)
            .execute();
      }
      Statement(stmt.get(), storage, logs).execute();
    }
    executed = true;
  } else if (!conditionalNode->elifClauses.empty()) {
    for (const auto &elifClause : conditionalNode->elifClauses) {
      if (checkTrueishnessOfExpression(elifClause.first, storage, logs)) {
        for (const auto &stmt : elifClause.second) {
          if (stmt->kind == NodeType::ReturnStmt) {
            storage.pop_back();
            return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()),
                                   storage, logs)
                .execute();
          }
          Statement(stmt.get(), storage, logs).execute();
        }
        executed = true;
        break;
      }
    }
  }
  if (!executed && !conditionalNode->elseBody.empty()) {
    for (const auto &stmt : conditionalNode->elseBody) {
      if (stmt->kind == NodeType::ReturnStmt) {
        storage.pop_back();
        return ReturnStatement(dynamic_cast<ReturnStmt *>(stmt.get()), storage,
                               logs)
            .execute();
      }
      Statement(stmt.get(), storage, logs).execute();
    }
  }
  storage.pop_back();
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::_NULL, 0);
}
