#ifndef LITERAL_EXPRESSION_HPP
#define LITERAL_EXPRESSION_HPP

#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"

class LiteralExpression {
public:
  LiteralExpression(Expr *expressionNode,
                    std::vector<std::shared_ptr<Storage>> storage,
                    std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  Expr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // LITERAL_EXPRESSION_HPP