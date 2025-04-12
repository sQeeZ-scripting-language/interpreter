#ifndef MEMBER_EXPRESSION_HPP
#define MEMBER_EXPRESSION_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class MemberExpression {
public:
  MemberExpression(MemberExpr *expressionNode,
                   std::vector<std::shared_ptr<Storage>> storage,
                   std::shared_ptr<Logs> logs);
  Storage::DataWrapper execute();

private:
  MemberExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
  std::shared_ptr<Logs> logs;
};

#endif // MEMBER_EXPRESSION_HPP