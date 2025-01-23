#include "interpreter/statements/return_statement.hpp"

ReturnStatement::ReturnStatement(ReturnStmt *returnNode,
                                 std::vector<std::shared_ptr<Storage>> storage)
    : returnNode(returnNode), storage(std::move(storage)) {}

Storage::DataWrapper ReturnStatement::execute() {
  return Expression(returnNode->value.get(), storage).execute();
}