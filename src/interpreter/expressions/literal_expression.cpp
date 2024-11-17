#include "interpreter/expressions/literal_expression.hpp"

LiteralExpression::LiteralExpression(Expr *expressionNode,
                                     std::shared_ptr<Storage> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper LiteralExpression::execute() {
  if (auto expr = dynamic_cast<Identifier *>(expressionNode)) {
    return storage->getEntry(expr->identifier.value);
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