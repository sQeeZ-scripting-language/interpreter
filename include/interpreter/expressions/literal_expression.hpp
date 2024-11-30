#ifndef LITERAL_EXPRESSION_HPP
#define LITERAL_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/utils.hpp"

class LiteralExpression {
public:
  LiteralExpression(Expr *expressionNode, std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  Expr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
};

#endif // LITERAL_EXPRESSION_HPP