#ifndef LOG_STATEMENT_HPP
#define LOG_STATEMENT_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class LogStatement {
public:
  LogStatement(LogStmt *logNode, std::vector<std::shared_ptr<Storage>> storage,
               std::shared_ptr<Logs> logs);
  void execute();

private:
  LogStmt *logNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
  void hexToRGB(const std::string &hex, int &r, int &g, int &b);
};

#endif // LOG_STATEMENT_HPP