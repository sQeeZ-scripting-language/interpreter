#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/statements/conditional_statement.hpp"
#include "interpreter/statements/declaration_statement.hpp"
#include "interpreter/statements/log_statement.hpp"
#include "interpreter/statements/loop_statement.hpp"
#include "interpreter/statements/return_statement.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class Statement {
public:
  Statement(Stmt *stmtNode, std::vector<std::shared_ptr<Storage>> storage,
            std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  Stmt *stmtNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // STATEMENT_HPP