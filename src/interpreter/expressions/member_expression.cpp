#include "interpreter/expressions/member_expression.hpp"

MemberExpression::MemberExpression(
    MemberExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper MemberExpression::execute() {
  Storage::DataWrapper object =
      Expression(dynamic_cast<Expr *>(expressionNode->object.get()), storage)
          .execute();
  if (object.dataType != Storage::DataType::OBJECT) {
    throw std::logic_error("Object expected!");
  }
  std::string property = "";
  if (expressionNode->computed) {
    Storage::DataWrapper propertyStr =
        Expression(dynamic_cast<Expr *>(expressionNode->property.get()),
                   storage)
            .execute();
    if (propertyStr.dataType != Storage::DataType::STRING) {
      throw std::logic_error("Property name must be a string!");
    }
    property = *propertyStr.data._string;
  } else {
    if (expressionNode->property->kind != NodeType::Identifier) {
      throw std::logic_error("Property name must be an identifier!");
    }
    property = dynamic_cast<Identifier *>(expressionNode->property.get())
                   ->identifier.value;
  }
  if (object.data._object->find(property) == object.data._object->end()) {
    throw std::logic_error("Property not found!");
  }
  return object.data._object->at(property);
}