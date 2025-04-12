#ifndef TERNARY_EXPRESSION_HPP
#define TERNARY_EXPRESSION_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class TernaryExpression {
public:
  TernaryExpression(TernaryExpr *expressionNode,
                    std::vector<std::shared_ptr<Storage>> storage,
                    std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  TernaryExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // TERNARY_EXPRESSION_HPP