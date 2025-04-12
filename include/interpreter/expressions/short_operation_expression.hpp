#ifndef SHORT_OPERATION_EXPRESSION_HPP
#define SHORT_OPERATION_EXPRESSION_HPP

#include "interpreter/data/array.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class ShortOperationExpression {
public:
  ShortOperationExpression(ShortOperationExpr *expressionNode,
                           std::vector<std::shared_ptr<Storage>> storage,
                           std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();
  Storage::DataWrapper executeExpression(Storage::DataWrapper leftValue);

private:
  ShortOperationExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // SHORT_OPERATION_EXPRESSION_HPP