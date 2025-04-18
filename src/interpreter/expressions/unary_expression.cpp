#include "interpreter/expressions/unary_expression.hpp"

UnaryExpression::UnaryExpression(UnaryExpr *expressionNode,
                                 std::vector<std::shared_ptr<Storage>> storage,
                                 std::shared_ptr<Logs> logs)
    : expressionNode(expressionNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper UnaryExpression::execute() {
  if (expressionNode->operator_.tag == Token::TypeTag::OPERATOR) {
    if (auto identifier =
            dynamic_cast<Identifier *>(expressionNode->operand.get())) {
      int keyIndex = storageKeyIndex(storage, identifier->identifier.value);
      if (keyIndex == -1) {
        throw std::logic_error("Variable not declared.");
      }
      Storage::DataWrapper previousValue =
          storage[keyIndex]->getEntry(identifier->identifier.value);
      Storage::DataWrapper newValue = Storage::DataWrapper(
          Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
      switch (expressionNode->operator_.type.operatorToken) {
      case OperatorToken::INCREMENT:
        newValue = BinaryExpression::addition(
            previousValue, Storage::DataWrapper(Storage::WrapperType::VALUE,
                                                Storage::DataType::INTEGER, 1));
        storage[keyIndex]->updateValue(identifier->identifier.value, newValue);
        return expressionNode->isPrefix ? newValue : previousValue;
      case OperatorToken::DECREMENT:
        newValue = BinaryExpression::subtraction(
            previousValue, Storage::DataWrapper(Storage::WrapperType::VALUE,
                                                Storage::DataType::INTEGER, 1));
        storage[keyIndex]->updateValue(identifier->identifier.value, newValue);
        return expressionNode->isPrefix ? newValue : previousValue;
      default:
        throw std::runtime_error("Unsupported unary operator.");
      }
    } else {
      throw std::logic_error("Operand must be an identifier.");
    }
  } else if (expressionNode->operator_.tag == Token::TypeTag::LOGICAL &&
             expressionNode->operator_.type.logicalToken == LogicalToken::NOT) {
    return _boolean(
        !checkTrueishnessOfExpression(expressionNode->operand, storage, logs));
  } else {
    throw std::runtime_error("Unsupported unary expression.");
  }
}