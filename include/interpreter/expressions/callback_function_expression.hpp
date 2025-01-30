#ifndef CALLBACK_FUNCTION_EXPRESSION_HPP
#define CALLBACK_FUNCTION_EXPRESSION_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/data/array.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class CallbackFunctionExpression {
public:
  CallbackFunctionExpression(CallbackFunctionExpr *expressionNode,
                 std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  CallbackFunctionExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;

  Storage::DataWrapper executeBody();
};

#endif // CALLBACK_FUNCTION_EXPRESSION_HPP