#ifndef ASSIGNMENT_EXPRESSION_HPP
#define ASSIGNMENT_EXPRESSION_HPP

#include "parser/ast_nodes.hpp"
#include "interpreter/storage.hpp"

class AssignmentExpression {
public:
  AssignmentExpression(AssignmentExpr *expressionNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  AssignmentExpr *expressionNode;
  std::shared_ptr<Storage> storage;
};

#endif // ASSIGNMENT_EXPRESSION_HPP