#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "interpreter/statements/log_statement.hpp"
#include "interpreter/statements/declaration_statement.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/storage.hpp"

class Statement {
public:
  Statement(Stmt *stmtNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  Stmt *stmtNode;
  std::shared_ptr<Storage> storage;
};

#endif // STATEMENT_HPP