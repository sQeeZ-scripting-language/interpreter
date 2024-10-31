#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "parser/ast_nodes.hpp"
#include "interpreter/storage.hpp"

#include "interpreter/expressions/assignment_expression.hpp"

class Expression {
public:
  Expression(Expr *exprNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  Expr *exprNode;
  std::shared_ptr<Storage> storage;
};

#endif // EXPRESSION_HPP