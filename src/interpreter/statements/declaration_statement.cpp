#include "interpreter/statements/declaration_statement.hpp"

DeclarationStatement::DeclarationStatement(FunctionDeclaration *declarationNode,
                                           std::shared_ptr<Storage> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

DeclarationStatement::DeclarationStatement(VarDeclaration *declarationNode,
                                           std::shared_ptr<Storage> storage)
    : declarationNode(declarationNode), storage(std::move(storage)) {}

void DeclarationStatement::execute() {
  if (std::holds_alternative<VarDeclaration *>(declarationNode)) {
    auto varDeclaration = std::get<VarDeclaration *>(declarationNode);
    for (const auto &declaration : varDeclaration->declarations) {
      if (declaration.second) {
        storage->setValue(declaration.first.value,
                          Storage::StorageType::VARIABLE,
                          static_cast<Expr *>(declaration.second.get()));
      }
    }
  } else if (std::holds_alternative<FunctionDeclaration *>(declarationNode)) {
    auto functionDeclaration = std::get<FunctionDeclaration *>(declarationNode);
    std::shared_ptr<FunctionDeclaration> funcPtr =
        std::shared_ptr<FunctionDeclaration>(functionDeclaration);
    storage->storeFunction(funcPtr->name.value, funcPtr);
  }
}
