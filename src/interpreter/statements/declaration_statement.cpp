#include "interpreter/statements/declaration_statement.hpp"

DeclarationStatement::DeclarationStatement(
    FunctionDeclaration *declarationNode,
    std::vector<std::shared_ptr<Storage>> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

DeclarationStatement::DeclarationStatement(
    VarDeclaration *declarationNode,
    std::vector<std::shared_ptr<Storage>> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

void DeclarationStatement::execute() {
  if (std::holds_alternative<VarDeclaration *>(declarationNode)) {
    executeVarDeclaration();
  } else if (std::holds_alternative<FunctionDeclaration *>(declarationNode)) {
    executeFunctionDeclaration();
  }
}

std::vector<std::string> DeclarationStatement::declareLoopVariables() {
  return executeVarDeclaration();
}

std::vector<std::string> DeclarationStatement::executeVarDeclaration() {
  auto varDeclaration = std::get<VarDeclaration *>(declarationNode);
  std::vector<std::string> declaredVariables = {};
  for (const auto &declaration : varDeclaration->declarations) {
    if (storage.back()->exists(declaration.first.value)) {
      throw std::logic_error("Identifier is already defined!");
    }
    Storage::DataWrapper value =
        declaration.second == nullptr
            ? Storage::DataWrapper(Storage::WrapperType::VALUE,
                                   Storage::DataType::_NULL, 0)
            : Expression(static_cast<Expr *>(declaration.second.get()), storage)
                  .execute();
    storage.back()->setValue(declaration.first.value, value);
    declaredVariables.push_back(declaration.first.value);
  }
  return declaredVariables;
}

void DeclarationStatement::executeFunctionDeclaration() {
  auto functionDeclaration = std::get<FunctionDeclaration *>(declarationNode);
  if (storage.back()->exists(functionDeclaration->name.value)) {
    throw std::logic_error("Identifier is already defined!");
  }
  storage.back()->setValue(functionDeclaration->name.value,
                           Storage::DataWrapper(Storage::WrapperType::FUNCTION,
                                                Storage::DataType::FUNCTION,
                                                functionDeclaration));
}
