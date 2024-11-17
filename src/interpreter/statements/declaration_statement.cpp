#include "interpreter/statements/declaration_statement.hpp"

DeclarationStatement::DeclarationStatement(FunctionDeclaration *declarationNode,
                                           std::shared_ptr<Storage> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

DeclarationStatement::DeclarationStatement(VarDeclaration *declarationNode,
                                           std::shared_ptr<Storage> storage)
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
      storage->setValue(
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
  storage->storeFunction(funcPtr->name.value, funcPtr);
}
