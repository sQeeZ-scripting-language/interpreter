#include "interpreter/expressions/callback_function_expression.hpp"

CallbackFunctionExpression::CallbackFunctionExpression(
    CallbackFunctionExpr *expressionNode,
    std::vector<std::shared_ptr<Storage>> storage)
    : expressionNode(expressionNode), storage(std::move(storage)) {}

Storage::DataWrapper CallbackFunctionExpression::execute() {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::CALLBACK_FUNCTION,
                              expressionNode);
}

Storage::DataWrapper CallbackFunctionExpression::executeBody(
    std::shared_ptr<Storage> parameterStorage) {
  Storage::DataWrapper returnValue = Storage::DataWrapper(
      Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
  storage.push_back(parameterStorage);
  storage.push_back(std::make_shared<Storage>());
  if (expressionNode->body.size() == 1) {
    returnValue = Statement(expressionNode->body[0].get(), storage).execute();
  } else if (expressionNode->body.size() > 1) {
    try {
      for (const auto &statement : expressionNode->body) {
        if (statement.get()->kind == NodeType::ReturnStmt) {
          returnValue =
              ReturnStatement(dynamic_cast<ReturnStmt *>(statement.get()),
                              storage)
                  .execute();
          break;
        } else {
          Statement(statement.get(), storage).execute();
        }
      }
    } catch (const std::exception &e) {
      handleException(e);
    }
  }
  storage.pop_back();
  storage.pop_back();
  return returnValue;
}