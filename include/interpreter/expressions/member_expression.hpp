#ifndef MEMBER_EXPRESSION_HPP
#define MEMBER_EXPRESSION_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

class MemberExpression {
public:
  MemberExpression(MemberExpr *expressionNode,
                   std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper execute();

private:
  MemberExpr *expressionNode;
  std::vector<std::shared_ptr<Storage>> storage;
};

#endif // MEMBER_EXPRESSION_HPP