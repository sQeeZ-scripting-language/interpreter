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
  Storage::DataWrapper subtraction(Storage::DataWrapper left, Storage::DataWrapper right);
  Storage::DataWrapper multiplication(Storage::DataWrapper left, Storage::DataWrapper right);
  Storage::DataWrapper division(Storage::DataWrapper left, Storage::DataWrapper right);
  Storage::DataWrapper modulus(Storage::DataWrapper left, Storage::DataWrapper right);
  Storage::DataWrapper potentiation(Storage::DataWrapper left, Storage::DataWrapper right);

  Storage::DataWrapper _integer(int value);
  Storage::DataWrapper _double(double value);
  Storage::DataWrapper stringAddition(std::string left, std::string right);
  Storage::DataWrapper stringMultiplication(std::string value, int multiplier);
};

#endif // BINARY_EXPRESSION_HPP