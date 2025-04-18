#ifndef UTILS_HPP
#define UTILS_HPP

#include <cctype>
#include <iostream>
#include <regex>
#include <string>

#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "parser/ast_nodes.hpp"

Storage::DataWrapper _integer(int value);
Storage::DataWrapper _double(double value);
Storage::DataWrapper _boolean(bool value);

bool checkTrueishnessOfExpression(const std::unique_ptr<Expr> &expr,
                                  std::vector<std::shared_ptr<Storage>> storage,
                                  std::shared_ptr<Logs> logs);
bool checkTrueishness(Storage::DataWrapper datawrapper,
                      std::vector<std::shared_ptr<Storage>> storage);
bool checkEquality(Storage::DataWrapper left, Storage::DataWrapper right,
                   bool equality);
bool checkGreater(Storage::DataWrapper left, Storage::DataWrapper right);
std::string toLowerCase(std::string str);
int storageKeyIndex(std::vector<std::shared_ptr<Storage>> storage,
                    std::string key);
void handleException(const std::exception &e);
std::string getPrintableValue(Storage::DataWrapper value);

#endif // UTILS_HPP