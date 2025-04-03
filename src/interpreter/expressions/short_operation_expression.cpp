#include "interpreter/expressions/short_operation_expression.hpp"

ShortOperationExpression::ShortOperationExpression(
    ShortOperationExpr *expressionNode,
    std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper ShortOperationExpression::execute() {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::SHORT_NOTATION_OPERATION,
                              expressionNode);
}

Storage::DataWrapper
ShortOperationExpression::executeExpression(Storage::DataWrapper leftValue) {
  Storage::DataWrapper rightValue =
      Expression(expressionNode->operand.get(), storage).execute();
  switch (expressionNode->operation.tag) {
  case Token::TypeTag::LOGICAL:
    if (expressionNode->operation.type.logicalToken == LogicalToken::GREATER) {
      return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                  Storage::DataType::BOOLEAN,
                                  checkGreater(leftValue, rightValue));
    } else if (expressionNode->operation.type.logicalToken ==
               LogicalToken::LESS) {
      return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                  Storage::DataType::BOOLEAN,
                                  checkGreater(rightValue, leftValue));
    } else if (expressionNode->operation.type.logicalToken ==
               LogicalToken::GREATER_EQUAL) {
      return Storage::DataWrapper(
          Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN,
          checkGreater(leftValue, rightValue) ||
              checkEquality(leftValue, rightValue, true));
    } else if (expressionNode->operation.type.logicalToken ==
               LogicalToken::LESS_EQUAL) {
      return Storage::DataWrapper(
          Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN,
          checkGreater(rightValue, leftValue) ||
              checkEquality(leftValue, rightValue, true));
    } else if (expressionNode->operation.type.logicalToken ==
               LogicalToken::EQUAL) {
      return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                  Storage::DataType::BOOLEAN,
                                  checkEquality(leftValue, rightValue, true));
    } else if (expressionNode->operation.type.logicalToken ==
               LogicalToken::NOT_EQUAL) {
      return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                  Storage::DataType::BOOLEAN,
                                  checkEquality(leftValue, rightValue, false));
    } else {
      throw std::invalid_argument("Invalid logical operation: " +
                                  expressionNode->operation.value);
    }
    break;
  case Token::TypeTag::OPERATOR:
    if (expressionNode->operation.type.operatorToken ==
        OperatorToken::ADDITION) {
      return BinaryExpression::addition(leftValue, rightValue);
    } else if (expressionNode->operation.type.operatorToken ==
               OperatorToken::SUBTRACTION) {
      return BinaryExpression::subtraction(leftValue, rightValue);
    } else if (expressionNode->operation.type.operatorToken ==
               OperatorToken::MULTIPLICATION) {
      return BinaryExpression::multiplication(leftValue, rightValue);
    } else if (expressionNode->operation.type.operatorToken ==
               OperatorToken::DIVISION) {
      return BinaryExpression::division(leftValue, rightValue);
    } else if (expressionNode->operation.type.operatorToken ==
               OperatorToken::MODULUS) {
      return BinaryExpression::modulus(leftValue, rightValue);
    } else if (expressionNode->operation.type.operatorToken ==
               OperatorToken::POTENTIATION) {
      return BinaryExpression::potentiation(leftValue, rightValue);
    } else {
      throw std::invalid_argument("Invalid operator operation: " +
                                  expressionNode->operation.value);
    }
    break;
  case Token::TypeTag::SHORT_NOTATION:
    break;
  default:
    throw std::invalid_argument("Invalid short operation: " +
                                expressionNode->operation.value);
  }
  throw std::invalid_argument("Invalid short operation: " +
                              expressionNode->operation.value);
}