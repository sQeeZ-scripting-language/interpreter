#include "interpreter/expressions/unary_expression.hpp"

UnaryExpression::UnaryExpression(UnaryExpr *expressionNode,
                                 std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper UnaryExpression::execute() {
  if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
    if (auto identifier =
            dynamic_cast<Identifier *>(expressionNode->operand.get())) {
      Storage::DataWrapper previousValue =
          storage->getEntry(identifier->identifier.value);
      Storage::DataWrapper newValue = Storage::DataWrapper(
          Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
      switch (expressionNode->operator_.type.operatorToken) {
      case OperatorToken::INCREMENT:
        newValue = BinaryExpression::addition(
            previousValue, Storage::DataWrapper(Storage::WrapperType::VALUE,
                                                Storage::DataType::INTEGER, 1));
        storage->updateValue(identifier->identifier.value, newValue);
        return expressionNode->isPrefix ? newValue : previousValue;
      case OperatorToken::DECREMENT:
        newValue = BinaryExpression::subtraction(
            previousValue, Storage::DataWrapper(Storage::WrapperType::VALUE,
                                                Storage::DataType::INTEGER, 1));
        storage->updateValue(identifier->identifier.value, newValue);
        return expressionNode->isPrefix ? newValue : previousValue;
      default:
        throw std::runtime_error("Unsupported unary operator.");
      }
    } else {
      throw std::logic_error("Operand must be an identifier.");
    }
  } else if (expressionNode->operator_.tag == Token::TypeTag::LOGICAL && expressionNode->operator_.type.logicalToken == LogicalToken::NOT) {
    return _boolean(!checkTrueishness(expressionNode->operand, storage));
  } else {
    throw std::runtime_error("Unsupported unary expression.");
  }
}