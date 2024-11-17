#ifndef UTILS_HPP
#define UTILS_HPP

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

bool checkTrueishness(const std::unique_ptr<Expr> &expr, std::shared_ptr<Storage> storage);

#endif // UTILS_HPP