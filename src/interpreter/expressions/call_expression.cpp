#include "interpreter/expressions/call_expression.hpp"

CallExpression::CallExpression(
    CallExpr *expressionNode, std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper CallExpression::execute() {
    if (expressionNode->caller == nullptr) {
        return functionCall();
    } else {
        return methodCall();
    }
}

Storage::DataWrapper CallExpression::functionCall() {
    Storage::DataWrapper function = Expression(expressionNode->method.get(), storage).execute();
    if (function.dataType != Storage::DataType::FUNCTION || function.wrapperType != Storage::WrapperType::FUNCTION) {
        throw std::runtime_error("Invalid function call!");
    }
    FunctionDeclaration *functionDeclaration = function.data._function;
    if (functionDeclaration->parameters.size() != expressionNode->args.size()) {
        throw std::runtime_error("Invalid number of arguments!");
    }
    int paramIndex = 0;
    std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
    for (auto &param : functionDeclaration->parameters) {
        if (parameterStorage.get()->exists(param.value)) {
            throw std::logic_error("Duplicated parameter name!");
        }
        parameterStorage.get()->setValue(param.value, Expression(expressionNode->args[paramIndex].get(), storage).execute());
        ++paramIndex;
    }
    storage.push_back(parameterStorage);
    storage.push_back(std::make_shared<Storage>());
    try {
        for (const auto &statement : functionDeclaration->body) {
            Statement(statement.get(), storage).execute();
        }
    } catch (const std::exception &e) {
        handleException(e);
    }
    storage.pop_back();
    storage.pop_back();
    // get result out of return statement
    return Storage::DataWrapper();
}

Storage::DataWrapper CallExpression::methodCall() {
    throw std::runtime_error("Method call not implemented!");
}
