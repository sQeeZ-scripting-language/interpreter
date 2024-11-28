#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include <cmath>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class BinaryExpression {
public:
  BinaryExpression(BinaryExpr *expressionNode,
                   std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

  static Storage::DataWrapper addition(Storage::DataWrapper left,
                                       Storage::DataWrapper right);
  static Storage::DataWrapper subtraction(Storage::DataWrapper left,
                                          Storage::DataWrapper right);
  static Storage::DataWrapper multiplication(Storage::DataWrapper left,
                                             Storage::DataWrapper right);
  static Storage::DataWrapper division(Storage::DataWrapper left,
                                       Storage::DataWrapper right);
  static Storage::DataWrapper modulus(Storage::DataWrapper left,
                                      Storage::DataWrapper right);
  static Storage::DataWrapper potentiation(Storage::DataWrapper left,
                                           Storage::DataWrapper right);

private:
  BinaryExpr *expressionNode;
  std::shared_ptr<Storage> storage;

  static Storage::DataWrapper _integer(int value);
  static Storage::DataWrapper _double(double value);
  static Storage::DataWrapper _boolean(bool value);
  static Storage::DataWrapper stringAddition(std::string left,
                                             std::string right);
  static Storage::DataWrapper stringMultiplication(std::string value,
                                                   int multiplier);
};

#endif // BINARY_EXPRESSION_HPP