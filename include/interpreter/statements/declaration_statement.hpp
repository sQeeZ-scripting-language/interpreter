#ifndef DECLARATION_STATEMENT_HPP
#define DECLARATION_STATEMENT_HPP

#include <variant>

#include "parser/ast_nodes.hpp"
#include "interpreter/storage.hpp"

class DeclarationStatement {
public:
  DeclarationStatement(FunctionDeclaration *declarationNode, std::shared_ptr<Storage> storage);
  DeclarationStatement(VarDeclaration *declarationNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  std::variant<VarDeclaration*, FunctionDeclaration*> declarationNode;
  std::shared_ptr<Storage> storage;
};

#endif // LOG_STATEMENT_HPP