#include "interpreter/expressions/short_operation_expression.hpp"

ShortOperationExpression::ShortOperationExpression(ShortOperationLiteral *expressionNode,
                                                   std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper ShortOperationExpression::execute() {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::SHORT_NOTATION_OPERATION, expressionNode);
}