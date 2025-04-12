#include "interpreter/statements/return_statement.hpp"

ReturnStatement::ReturnStatement(ReturnStmt *returnNode,
                                 std::vector<std::shared_ptr<Storage>> storage,
                                 std::shared_ptr<Logs> logs)
    : returnNode(returnNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper ReturnStatement::execute() {
  return Expression(returnNode->value.get(), storage, logs).execute();
}