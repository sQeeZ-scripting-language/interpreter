#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class ReturnStatement {
public:
  ReturnStatement(ReturnStmt *returnNode,
                  std::vector<std::shared_ptr<Storage>> storage,
                  std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  ReturnStmt *returnNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // RETURN_STATEMENT_HPP