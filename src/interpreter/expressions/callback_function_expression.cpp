#include "interpreter/expressions/callback_function_expression.hpp"

CallbackFunctionExpression::CallbackFunctionExpression(CallbackFunctionExpr *expressionNode,
                                                       std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper CallbackFunctionExpression::execute() {
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::CALLBACK_FUNCTION, expressionNode);
}

Storage::DataWrapper CallbackFunctionExpression::executeBody() {
    Storage::DataWrapper returnValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    if (expressionNode->body.empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    } else if (expressionNode->body.size() == 1) {
        return Statement(expressionNode->body[0].get(), storage).execute();
    } else {
        Storage::DataWrapper returnValue = Storage::DataWrapper();
        try {
            for (const auto &statement : expressionNode->body) {
                if (statement.get()->kind == NodeType::ReturnStmt) {
                    returnValue = ReturnStatement(
                                    dynamic_cast<ReturnStmt *>(statement.get()), storage)
                                    .execute();
                    break;
                } else {
                    Statement(statement.get(), storage).execute();
                }
            }
        } catch (const std::exception &e) {
            handleException(e);
        }
        return returnValue;
    }
}