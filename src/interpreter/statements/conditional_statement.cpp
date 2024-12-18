#include "interpreter/statements/conditional_statement.hpp"

ConditionalStatement::ConditionalStatement(
    ConditionalStmt *conditionalNode,
    std::vector<std::shared_ptr<Storage>> storage)
    : conditionalNode(conditionalNode), storage(std::move(storage)) {}

void ConditionalStatement::execute() {
  bool executed = false;
  storage.push_back(std::make_shared<Storage>());
  if (checkTrueishness(conditionalNode->ifClause.first, storage)) {
    for (const auto &stmt : conditionalNode->ifClause.second) {
      Statement(stmt.get(), storage).execute();
    }
    executed = true;
  } else if (!conditionalNode->elifClauses.empty()) {
    for (const auto &elifClause : conditionalNode->elifClauses) {
      if (checkTrueishness(elifClause.first, storage)) {
        for (const auto &stmt : elifClause.second) {
          Statement(stmt.get(), storage).execute();
        }
        executed = true;
        break;
      }
    }
  }
  if (!executed && !conditionalNode->elseBody.empty()) {
    for (const auto &stmt : conditionalNode->elseBody) {
      Statement(stmt.get(), storage).execute();
    }
  }
  storage.pop_back();
}
