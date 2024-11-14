#include "interpreter/expressions/binary_expression.hpp"

BinaryExpression::BinaryExpression(BinaryExpr *expressionNode,
                                   std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper BinaryExpression::execute() {
  if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
    std::cout << expressionNode->toString() << std::endl;
  } else {
    throw std::logic_error("Unsupported binary expression!");
  }
}