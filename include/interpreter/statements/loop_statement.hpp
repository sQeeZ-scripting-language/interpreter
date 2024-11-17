#ifndef LOOP_STATEMENT_HPP
#define LOOP_STATEMENT_HPP

#include <variant>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class LoopStatement {
public:
  LoopStatement(WhileStmt *loopNode, std::shared_ptr<Storage> storage);
  LoopStatement(DoWhileStmt *loopNode, std::shared_ptr<Storage> storage);
  LoopStatement(ForStmt *loopNode, std::shared_ptr<Storage> storage);
  LoopStatement(ForInStmt *loopNode, std::shared_ptr<Storage> storage);
  LoopStatement(ForOfStmt *loopNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  std::variant<WhileStmt *, DoWhileStmt *, ForStmt *, ForInStmt *, ForOfStmt *> declarationNode;
  std::shared_ptr<Storage> storage;
};

#endif // LOOP_STATEMENT_HPP