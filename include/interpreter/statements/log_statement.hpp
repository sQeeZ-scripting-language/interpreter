#ifndef LOG_STATEMENT_HPP
#define LOG_STATEMENT_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class LogStatement {
public:
  LogStatement(LogStmt *logNode, std::shared_ptr<Storage> storage);
  void execute();

private:
  LogStmt *logNode;
  std::shared_ptr<Storage> storage;
  std::string getMessage();
  void hexToRGB(const std::string &hex, int &r, int &g, int &b);
  std::string castStorageEntry(const std::string &name);
};

#endif // LOG_STATEMENT_HPP