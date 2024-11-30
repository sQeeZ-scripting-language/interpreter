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

void DeclarationStatement::executeVarDeclaration() {
  auto varDeclaration = std::get<VarDeclaration *>(declarationNode);
  for (const auto &declaration : varDeclaration->declarations) {
    if (declaration.second) {
      if (storageKeyIndex(storage, declaration.first.value) != -1) {
        throw std::logic_error("Variable already declared.");
      }
      storage.back()->setValue(
          declaration.first.value,
          Expression(static_cast<Expr *>(declaration.second.get()), storage)
              .execute());
    }
  }
}

void DeclarationStatement::executeFunctionDeclaration() {
  auto functionDeclaration = std::get<FunctionDeclaration *>(declarationNode);
  std::shared_ptr<FunctionDeclaration> funcPtr =
      std::shared_ptr<FunctionDeclaration>(functionDeclaration);
  if (functionKeyIndex(storage, functionDeclaration->name.value) != -1) {
    throw std::logic_error("Function already declared.");
  }
  storage.back()->storeFunction(funcPtr->name.value, funcPtr);
}
