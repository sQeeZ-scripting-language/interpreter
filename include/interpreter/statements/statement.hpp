#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "parser/ast_nodes.hpp"
#include "interpreter/statements/log_statement.hpp"

class Statement {
public:
   Statement(Stmt* stmtNode);
   void execute();

private:
    Stmt* stmtNode;
};

#endif