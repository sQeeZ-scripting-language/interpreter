#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "interpreter/statements/log_statement.hpp"
#include "parser/ast_nodes.hpp"

class Statement {
public:
  Statement(Stmt *stmtNode);
  void execute();

private:
  Stmt *stmtNode;
};

#endif // STATEMENT_HPP