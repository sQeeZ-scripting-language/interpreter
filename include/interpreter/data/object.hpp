#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "interpreter/expressions/callback_function_expression.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"
#include <string>
#include <unordered_map>

enum class ObjectMethod { HAS_KEY, KEYS, VALUES, ENTRIES, GET };

class Object {
public:
  Storage::DataWrapper
  callMethod(std::string method, Expr *caller,
             const std::vector<std::unique_ptr<Expr>> args,
             std::vector<std::shared_ptr<Storage>> storage);

private:
  inline static const std::unordered_map<std::string, ObjectMethod>
      stringToEnumMap = {{"hasKey", ObjectMethod::HAS_KEY},
                         {"keys", ObjectMethod::KEYS},
                         {"values", ObjectMethod::VALUES},
                         {"entries", ObjectMethod::ENTRIES},
                         {"get", ObjectMethod::GET}};

  Storage::DataWrapper hasKey(std::string method, Expr *caller,
                              Storage::DataWrapper callerValue,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper keys(std::string method, Expr *caller,
                            Storage::DataWrapper callerValue,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper values(std::string method, Expr *caller,
                              Storage::DataWrapper callerValue,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper entries(std::string method, Expr *caller,
                               Storage::DataWrapper callerValue,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage);
  Storage::DataWrapper get(std::string method, Expr *caller,
                           Storage::DataWrapper callerValue,
                           const std::vector<std::unique_ptr<Expr>> &args,
                           std::vector<std::shared_ptr<Storage>> storage);
};

#endif // OBJECT_HPP