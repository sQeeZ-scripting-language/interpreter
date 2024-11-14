#ifndef UNARY_EXPRESSION_HPP
#define UNARY_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/expressions/binary_expression.hpp"

class UnaryExpression {
public:
  UnaryExpression(UnaryExpr *expressionNode, std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

private:
  UnaryExpr *expressionNode;
  std::shared_ptr<Storage> storage;
};

#endif // UNARY_EXPRESSION_HPP