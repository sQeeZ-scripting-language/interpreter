#ifndef DECLARATION_STATEMENT_HPP
#define DECLARATION_STATEMENT_HPP

#include <variant>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class DeclarationStatement {
public:
  DeclarationStatement(FunctionDeclaration *declarationNode,
                       std::vector<std::shared_ptr<Storage>> storage);
  DeclarationStatement(VarDeclaration *declarationNode,
                       std::vector<std::shared_ptr<Storage>> storage);
  void execute();
  std::vector<std::string> declareLoopVariables();

private:
  std::variant<VarDeclaration *, FunctionDeclaration *> declarationNode;
  std::vector<std::shared_ptr<Storage>> storage;

  std::vector<std::string> executeVarDeclaration();
  void executeFunctionDeclaration();
};

#endif // DECLARATION_STATEMENT_HPP