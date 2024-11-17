#ifndef LITERAL_EXPRESSION_HPP
#define LITERAL_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class LiteralExpression {
public:
  LiteralExpression(Expr *expressionNode, std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

private:
  Expr *expressionNode;
  std::shared_ptr<Storage> storage;
};

#endif // LITERAL_EXPRESSION_HPP