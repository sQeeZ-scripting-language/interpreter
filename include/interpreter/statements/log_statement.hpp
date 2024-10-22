#ifndef LOG_STATEMENT_HPP
#define LOG_STATEMENT_HPP

#include "parser/ast_nodes.hpp"

class LogStatement {
public:
  LogStatement(LogStmt *logNode);
  void execute();

private:
  LogStmt *logNode;
  auto getMessage();
  void hexToRGB(const std::string &hex, int &r, int &g, int &b);
};

#endif // LOG_STATEMENT_HPP