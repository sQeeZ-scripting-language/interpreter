#include "interpreter/expressions/short_operation_expression.hpp"

ShortOperationExpression::ShortOperationExpression(ShortOperationLiteral *expressionNode,
                                                   std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper ShortOperationExpression::execute() {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::SHORT_NOTATION_OPERATION, expressionNode);
}

Storage::DataWrapper ShortOperationExpression::executeExpression(Storage::DataWrapper leftValue) {
    Storage::DataWrapper rightValue = Expression(expressionNode->operand.get(), storage).execute();

    switch (expressionNode->operation.tag) {
        case Token::TypeTag::LOGICAL:
            break;
        case Token::TypeTag::OPERATOR:
            break;
        case Token::TypeTag::SHORT_NOTATION:
            break;
        default:
            throw std::invalid_argument("Invalid short operation: " + expressionNode->operation.value);
    }
}