#ifndef CONDITIONAL_STATEMENT_HPP
#define CONDITIONAL_STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/utils.hpp"

class ConditionalStatement {
public:
  ConditionalStatement(ConditionalStmt *conditionalNode,
                       std::shared_ptr<Storage> storage);
  void execute();

private:
  ConditionalStmt *conditionalNode;
  std::shared_ptr<Storage> storage;
};

#endif // CONDITIONAL_STATEMENT_HPP