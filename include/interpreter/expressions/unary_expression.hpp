#ifndef UNARY_EXPRESSION_HPP
#define UNARY_EXPRESSION_HPP

#include "interpreter/expressions/binary_expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class UnaryExpression {
public:
  UnaryExpression(UnaryExpr *expressionNode,
                  std::vector<std::shared_ptr<Storage>> storage,
                  std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  UnaryExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // UNARY_EXPRESSION_HPP