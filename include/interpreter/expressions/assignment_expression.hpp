#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "interpreter/expressions/expression.hpp"
#include "parser/ast_nodes.hpp"

class AssignmentExpression {
public:
  AssignmentExpression(Expr *expressionNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  Expr *expressionNode;
  std::shared_ptr<Storage> storage;
};

#endif // ASSIGNMENT_EXPRESSION_HPP