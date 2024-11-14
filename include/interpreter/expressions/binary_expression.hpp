#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class BinaryExpression {
public:
  BinaryExpression(BinaryExpr *expressionNode,
                   std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

private:
  BinaryExpr *expressionNode;
  std::shared_ptr<Storage> storage;
};

#endif // BINARY_EXPRESSION_HPP