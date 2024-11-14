#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "interpreter/expressions/expression.hpp"
#include "parser/ast_nodes.hpp"

class BinaryExpression {
public:
  BinaryExpression(BinaryExpr *expressionNode,
                   std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

private:
  BinaryExpr *expressionNode;
  std::shared_ptr<Storage> storage;

  Storage::DataWrapper addition(Storage::DataWrapper left, Storage::DataWrapper right);

  Storage::DataWrapper integerAddition(int left, int right);
  Storage::DataWrapper doubleAddition(double left, double right);
  Storage::DataWrapper stringAddition(std::string left, std::string right);
};

#endif // BINARY_EXPRESSION_HPP