#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

#include "interpreter/expressions/assignment_expression.hpp"
#include "interpreter/expressions/binary_expression.hpp"
#include "interpreter/expressions/literal_expression.hpp"
#include "interpreter/expressions/unary_expression.hpp"

class Expression {
public:
  Expression(Expr *exprNode, std::shared_ptr<Storage> storage);
  Storage::DataWrapper execute();

private:
  Expr *exprNode;
  std::shared_ptr<Storage> storage;
};

#endif // EXPRESSION_HPP