#include "interpreter/expressions/call_expression.hpp"

CallExpression::CallExpression(CallExpr *expressionNode,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::shared_ptr<Logs> logs)
    : expressionNode(expressionNode), storage(std::move(storage)), logs(logs) {}

Storage::DataWrapper CallExpression::execute() {
  if (expressionNode->caller == nullptr) {
    return functionCall();
  } else {
    return methodCall();
  }
}

Storage::DataWrapper CallExpression::functionCall() {
  Storage::DataWrapper function =
      Expression(expressionNode->method.get(), storage, logs).execute();
  if (function.dataType != Storage::DataType::FUNCTION ||
      function.wrapperType != Storage::WrapperType::FUNCTION) {
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
    parameterStorage.get()->setValue(
        param.value,
        Expression(expressionNode->args[paramIndex].get(), storage, logs)
            .execute());
    ++paramIndex;
  }
  storage.push_back(parameterStorage);
  storage.push_back(std::make_shared<Storage>());
  Storage::DataWrapper returnValue = Storage::DataWrapper();
  try {
    for (const auto &statement : functionDeclaration->body) {
      if (statement.get()->kind == NodeType::ReturnStmt) {
        returnValue =
            ReturnStatement(dynamic_cast<ReturnStmt *>(statement.get()),
                            storage, logs)
                .execute();
        break;
      } else {
        Statement(statement.get(), storage, logs).execute();
      }
    }
  } catch (const std::exception &e) {
    handleException(e);
  }
  storage.pop_back();
  storage.pop_back();
  return returnValue;
}

Storage::DataWrapper CallExpression::methodCall() {
  Storage::DataWrapper caller =
      Expression(expressionNode->caller.get(), storage, logs).execute();
  if (expressionNode->method.get()->kind != NodeType::Identifier) {
    throw std::runtime_error("Invalid method call!");
  }
  if (caller.dataType == Storage::DataType::OBJECT) {
    Object object;
    return object.callMethod(
        dynamic_cast<Identifier *>(expressionNode->method.get())
            ->identifier.value,
        expressionNode->caller.get(), std::move(expressionNode->args), storage,
        logs);
  } else if (caller.dataType == Storage::DataType::ARRAY) {
    Array array;
    std::string identifier = "";
    if (auto *identifierNode =
            dynamic_cast<Identifier *>(expressionNode->caller.get())) {
      identifier = identifierNode->identifier.value;
    }
    return array.callMethod(
        dynamic_cast<Identifier *>(expressionNode->method.get())
            ->identifier.value,
        caller, std::move(expressionNode->args), storage, identifier, logs);
  } else {
    throw std::runtime_error("Invalid method call!");
  }
}
