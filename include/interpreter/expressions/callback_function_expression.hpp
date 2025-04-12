#ifndef CALLBACK_FUNCTION_EXPRESSION_HPP
#define CALLBACK_FUNCTION_EXPRESSION_HPP

#include "interpreter/data/array.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class CallbackFunctionExpression {
public:
  CallbackFunctionExpression(CallbackFunctionExpr *expressionNode,
                             std::vector<std::shared_ptr<Storage>> storage,
                             std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();
  Storage::DataWrapper executeBody(std::shared_ptr<Storage> parameterStorage);

private:
  CallbackFunctionExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // CALLBACK_FUNCTION_EXPRESSION_HPP