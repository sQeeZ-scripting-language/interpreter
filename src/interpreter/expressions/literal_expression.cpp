#include "interpreter/expressions/literal_expression.hpp"

LiteralExpression::LiteralExpression(
    Expr *expressionNode, std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper LiteralExpression::execute() {
  if (auto expr = dynamic_cast<Identifier *>(expressionNode)) {
    int keyIndex = storageKeyIndex(storage, expr->identifier.value);
    if (keyIndex == -1) {
      throw std::logic_error("Variable not declared.");
    }
    return storage[keyIndex]->getEntry(expr->identifier.value);
  } else if (auto expr = dynamic_cast<ArrayLiteral *>(expressionNode)) {
    std::vector<Storage::DataWrapper> elements;
    for (const auto &element : expr->elements) {
      elements.push_back(Expression(element.get(), storage).execute());
    }
    return Storage::DataWrapper(
        Storage::WrapperType::VALUE, Storage::DataType::ARRAY,
        new std::vector<Storage::DataWrapper>(elements));
  } else if (auto expr = dynamic_cast<ObjectLiteral *> (expressionNode)) {
    std::unordered_map<std::string, Storage::DataWrapper> elements;
    for (const auto &property : expr->properties) {
      elements[property.get()->key.value] = Expression(property.get()->value.get(), storage).execute();
    }
    return Storage::DataWrapper(
        Storage::WrapperType::VALUE, Storage::DataType::OBJECT,
        new std::unordered_map<std::string, Storage::DataWrapper>(elements));
  } else if (auto expr = dynamic_cast<IntegerLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::INTEGER, expr->value);
  } else if (auto expr = dynamic_cast<DoubleLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::DOUBLE, expr->value);
  } else if (auto expr = dynamic_cast<BooleanLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::BOOLEAN, expr->value);
  } else if (auto expr = dynamic_cast<CharLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::CHAR, expr->value);
  } else if (auto expr = dynamic_cast<StringLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::STRING,
                                new std::string(expr->value));
  } else if (auto expr = dynamic_cast<HexCodeLiteral *>(expressionNode)) {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::HEXCODE,
                                new std::string(expr->value));
  } else {
    return Storage::DataWrapper(Storage::WrapperType::VALUE,
                                Storage::DataType::_NULL, 0);
  }
}