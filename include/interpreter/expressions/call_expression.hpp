#ifndef CALL_EXPRESSION_HPP
#define CALL_EXPRESSION_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "interpreter/statements/statement.hpp"
#include "parser/ast_nodes.hpp"

class CallExpression {
public:
  CallExpression(CallExpr *expressionNode,
                   std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  CallExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;

  Storage::DataWrapper functionCall();
  Storage::DataWrapper methodCall();
};

#endif // CALL_EXPRESSION_HPP