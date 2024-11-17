#ifndef CONDITIONAL_STATEMENT_HPP
#define CONDITIONAL_STATEMENT_HPP

#include "interpreter/statements/statement.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class ConditionalStatement {
public:
  ConditionalStatement(ConditionalStmt *conditionalNode,
                       std::shared_ptr<Storage> storage);
  void execute();

private:
  ConditionalStmt *conditionalNode;
  std::shared_ptr<Storage> storage;

  bool checkTrusishness(const std::unique_ptr<Expr> &expr);
};

#endif // CONDITIONAL_STATEMENT_HPP