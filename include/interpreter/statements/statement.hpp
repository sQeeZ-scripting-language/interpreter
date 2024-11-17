#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/statements/declaration_statement.hpp"
#include "interpreter/statements/log_statement.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class Statement {
public:
  Statement(Stmt *stmtNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  Stmt *stmtNode;
  std::shared_ptr<Storage> storage;
};

#endif // STATEMENT_HPP