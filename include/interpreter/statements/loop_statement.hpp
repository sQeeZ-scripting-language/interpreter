#ifndef LOOP_STATEMENT_HPP
#define LOOP_STATEMENT_HPP

#include <variant>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/statements/statement.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class LoopStatement {
public:
  LoopStatement(WhileStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  LoopStatement(DoWhileStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  LoopStatement(ForStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  LoopStatement(ForInStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  LoopStatement(ForOfStmt *loopNode,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  std::variant<WhileStmt *, DoWhileStmt *, ForStmt *, ForInStmt *, ForOfStmt *>
      loopNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;

  Storage::DataWrapper executeWhileLoop();
  Storage::DataWrapper executeDoWhileLoop();
  Storage::DataWrapper executeForLoop();
  Storage::DataWrapper executeForOfLoop();
  Storage::DataWrapper executeForInLoop();
};

#endif // LOOP_STATEMENT_HPP