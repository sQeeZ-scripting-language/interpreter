#ifndef UTILS_HPP
#define UTILS_HPP

#include <cctype>
#include <string>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

bool checkTrueishness(const std::unique_ptr<Expr> &expr,
                      std::shared_ptr<Storage> storage);
bool checkEquality(Storage::DataWrapper left, Storage::DataWrapper right,
                   bool equality);
std::string toLowerCase(std::string str);

#endif // UTILS_HPP