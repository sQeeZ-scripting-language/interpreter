#ifndef SHORT_OPERATION_EXPRESSION_HPP
#define SHORT_OPERATION_EXPRESSION_HPP

#include "interpreter/data/array.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class ShortOperationExpression {
public:
  ShortOperationExpression(ShortOperationLiteral *expressionNode,
                             std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  ShortOperationLiteral *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
};

#endif // SHORT_OPERATION_EXPRESSION_HPP