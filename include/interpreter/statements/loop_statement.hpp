#ifndef LOOP_STATEMENT_HPP
#define LOOP_STATEMENT_HPP

#include <variant>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class LoopStatement {
public:
  LoopStatement(WhileStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage);
  LoopStatement(DoWhileStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage);
  LoopStatement(ForStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage);
  LoopStatement(ForInStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage);
  LoopStatement(ForOfStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  std::variant<WhileStmt *, DoWhileStmt *, ForStmt *, ForInStmt *, ForOfStmt *>
      loopNode;
  std::vector<std::shared_ptr<Storage>> storage;

  Storage::DataWrapper executeWhileLoop();
  Storage::DataWrapper executeDoWhileLoop();
  Storage::DataWrapper executeForLoop();
  Storage::DataWrapper executeForOfLoop();
  Storage::DataWrapper executeForInLoop();
};

#endif // LOOP_STATEMENT_HPP