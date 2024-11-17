#include "interpreter/statements/conditional_statement.hpp"

ConditionalStatement::ConditionalStatement(ConditionalStmt *conditionalNode,
                                           std::shared_ptr<Storage> storage)
    : conditionalNode(conditionalNode), storage(std::move(storage)) {}

void ConditionalStatement::execute() {
  bool executed = false;
  if (checkTrusishness(conditionalNode->ifClause.first)) {
    for (const auto &stmt : conditionalNode->ifClause.second) {
      Statement(stmt.get(), storage).execute();
    }
    executed = true;
  } else if (!conditionalNode->elifClauses.empty()) {
    for (const auto &elifClause : conditionalNode->elifClauses) {
      if (checkTrusishness(elifClause.first)) {
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
}

bool ConditionalStatement::checkTrusishness(const std::unique_ptr<Expr> &expr) {
  Storage::DataWrapper datawrapper = Expression(expr.get(), storage).execute();
  switch (datawrapper.dataType) {
  case Storage::DataType::BOOLEAN:
    return datawrapper.data._bool;
  case Storage::DataType::INTEGER:
    return datawrapper.data._int != 0;
  case Storage::DataType::DOUBLE:
    return datawrapper.data._double != 0.0;
  case Storage::DataType::STRING:
    return !datawrapper.data._string->empty();
  case Storage::DataType::CHAR:
    return datawrapper.data._char != '\0';
  case Storage::DataType::_NULL:
  default:
    return false;
  }
}