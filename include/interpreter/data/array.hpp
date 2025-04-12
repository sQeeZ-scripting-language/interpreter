#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "interpreter/expressions/callback_function_expression.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/logs.hpp"
#include "interpreter/storage.hpp"
#include "interpreter/utils.hpp"
#include "parser/ast_nodes.hpp"
#include <string>
#include <unordered_map>

enum class ArrayMethod {
  LENGTH,
  // Mutating methods
  PUSH,
  POP,
  SHIFT,
  UNSHIFT,
  SPLICE,
  REVERSE,
  SORT,
  FILL,
  // Non-mutating methods
  CONCAT,
  SLICE,
  INCLUDES,
  INDEX_OF,
  LAST_INDEX_OF,
  JOIN,
  EVERY,
  SOME,
  FIND,
  FIND_INDEX,
  FIND_LAST,
  FIND_LAST_INDEX,
  FILTER,
  MAP,
  REDUCE,
  FLAT,
  FLAT_MAP,
  FOR_EACH
};

class Array {
public:
  Storage::DataWrapper callMethod(std::string method,
                                  Storage::DataWrapper caller,
                                  const std::vector<std::unique_ptr<Expr>> args,
                                  std::vector<std::shared_ptr<Storage>> storage,
                                  std::string identifier,
                                  std::shared_ptr<Logs> logs);

private:
  inline static const std::unordered_map<std::string, ArrayMethod>
      stringToEnumMap = {{"length", ArrayMethod::LENGTH},
                         {"push", ArrayMethod::PUSH},
                         {"pop", ArrayMethod::POP},
                         {"shift", ArrayMethod::SHIFT},
                         {"unshift", ArrayMethod::UNSHIFT},
                         {"splice", ArrayMethod::SPLICE},
                         {"reverse", ArrayMethod::REVERSE},
                         {"sort", ArrayMethod::SORT},
                         {"fill", ArrayMethod::FILL},
                         {"concat", ArrayMethod::CONCAT},
                         {"slice", ArrayMethod::SLICE},
                         {"includes", ArrayMethod::INCLUDES},
                         {"indexOf", ArrayMethod::INDEX_OF},
                         {"lastIndexOf", ArrayMethod::LAST_INDEX_OF},
                         {"join", ArrayMethod::JOIN},
                         {"every", ArrayMethod::EVERY},
                         {"some", ArrayMethod::SOME},
                         {"find", ArrayMethod::FIND},
                         {"findIndex", ArrayMethod::FIND_INDEX},
                         {"findLast", ArrayMethod::FIND_LAST},
                         {"findLastIndex", ArrayMethod::FIND_LAST_INDEX},
                         {"filter", ArrayMethod::FILTER},
                         {"map", ArrayMethod::MAP},
                         {"reduce", ArrayMethod::REDUCE},
                         {"flat", ArrayMethod::FLAT},
                         {"flatMap", ArrayMethod::FLAT_MAP},
                         {"forEach", ArrayMethod::FOR_EACH}};

  Storage::DataWrapper length(std::string method, Storage::DataWrapper caller,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage,
                              std::shared_ptr<Logs> logs);
  Storage::DataWrapper push(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::string identifier, std::shared_ptr<Logs> logs);
  Storage::DataWrapper pop(std::string method, Storage::DataWrapper caller,
                           const std::vector<std::unique_ptr<Expr>> &args,
                           std::vector<std::shared_ptr<Storage>> storage,
                           std::string identifier, std::shared_ptr<Logs> logs);
  Storage::DataWrapper shift(std::string method, Storage::DataWrapper caller,
                             const std::vector<std::unique_ptr<Expr>> &args,
                             std::vector<std::shared_ptr<Storage>> storage,
                             std::string identifier,
                             std::shared_ptr<Logs> logs);
  Storage::DataWrapper unshift(std::string method, Storage::DataWrapper caller,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::string identifier,
                               std::shared_ptr<Logs> logs);
  Storage::DataWrapper splice(std::string method, Storage::DataWrapper caller,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage,
                              std::string identifier,
                              std::shared_ptr<Logs> logs);
  Storage::DataWrapper reverse(std::string method, Storage::DataWrapper caller,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::string identifier,
                               std::shared_ptr<Logs> logs);
  Storage::DataWrapper sort(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::string identifier, std::shared_ptr<Logs> logs);
  Storage::DataWrapper fill(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::string identifier, std::shared_ptr<Logs> logs);
  Storage::DataWrapper concat(std::string method, Storage::DataWrapper caller,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage,
                              std::shared_ptr<Logs> logs);
  Storage::DataWrapper slice(std::string method, Storage::DataWrapper caller,
                             const std::vector<std::unique_ptr<Expr>> &args,
                             std::vector<std::shared_ptr<Storage>> storage,
                             std::shared_ptr<Logs> logs);
  Storage::DataWrapper includes(std::string method, Storage::DataWrapper caller,
                                const std::vector<std::unique_ptr<Expr>> &args,
                                std::vector<std::shared_ptr<Storage>> storage,
                                std::shared_ptr<Logs> logs);
  Storage::DataWrapper indexOf(std::string method, Storage::DataWrapper caller,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::shared_ptr<Logs> logs);
  Storage::DataWrapper
  lastIndexOf(std::string method, Storage::DataWrapper caller,
              const std::vector<std::unique_ptr<Expr>> &args,
              std::vector<std::shared_ptr<Storage>> storage,
              std::shared_ptr<Logs> logs);
  Storage::DataWrapper join(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::shared_ptr<Logs> logs);
  Storage::DataWrapper every(std::string method, Storage::DataWrapper caller,
                             const std::vector<std::unique_ptr<Expr>> &args,
                             std::vector<std::shared_ptr<Storage>> storage,
                             std::shared_ptr<Logs> logs);
  Storage::DataWrapper some(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::shared_ptr<Logs> logs);
  Storage::DataWrapper find(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::shared_ptr<Logs> logs);
  Storage::DataWrapper findIndex(std::string method,
                                 Storage::DataWrapper caller,
                                 const std::vector<std::unique_ptr<Expr>> &args,
                                 std::vector<std::shared_ptr<Storage>> storage,
                                 std::shared_ptr<Logs> logs);
  Storage::DataWrapper findLast(std::string method, Storage::DataWrapper caller,
                                const std::vector<std::unique_ptr<Expr>> &args,
                                std::vector<std::shared_ptr<Storage>> storage,
                                std::shared_ptr<Logs> logs);
  Storage::DataWrapper
  findLastIndex(std::string method, Storage::DataWrapper caller,
                const std::vector<std::unique_ptr<Expr>> &args,
                std::vector<std::shared_ptr<Storage>> storage,
                std::shared_ptr<Logs> logs);
  Storage::DataWrapper filter(std::string method, Storage::DataWrapper caller,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage,
                              std::shared_ptr<Logs> logs);
  Storage::DataWrapper map(std::string method, Storage::DataWrapper caller,
                           const std::vector<std::unique_ptr<Expr>> &args,
                           std::vector<std::shared_ptr<Storage>> storage,
                           std::shared_ptr<Logs> logs);
  Storage::DataWrapper reduce(std::string method, Storage::DataWrapper caller,
                              const std::vector<std::unique_ptr<Expr>> &args,
                              std::vector<std::shared_ptr<Storage>> storage,
                              std::shared_ptr<Logs> logs);
  Storage::DataWrapper flat(std::string method, Storage::DataWrapper caller,
                            const std::vector<std::unique_ptr<Expr>> &args,
                            std::vector<std::shared_ptr<Storage>> storage,
                            std::shared_ptr<Logs> logs);
  Storage::DataWrapper flatMap(std::string method, Storage::DataWrapper caller,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::shared_ptr<Logs> logs);
  Storage::DataWrapper forEach(std::string method, Storage::DataWrapper caller,
                               const std::vector<std::unique_ptr<Expr>> &args,
                               std::vector<std::shared_ptr<Storage>> storage,
                               std::shared_ptr<Logs> logs);

  // Utils
  Storage::DataWrapper flattenArray(Storage::DataWrapper array, int depth);
};

#endif // ARRAY_HPP
