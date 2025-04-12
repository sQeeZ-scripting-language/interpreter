#ifndef CONDITIONAL_STATEMENT_HPP
#define CONDITIONAL_STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class ConditionalStatement {
public:
  ConditionalStatement(ConditionalStmt *conditionalNode,
                       std::vector<std::shared_ptr<Storage>> storage,
                       std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  ConditionalStmt *conditionalNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // CONDITIONAL_STATEMENT_HPP