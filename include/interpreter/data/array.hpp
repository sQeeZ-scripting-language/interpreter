#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <unordered_map>
#include <string>
#include "interpreter/storage.hpp"
#include "interpreter/expressions/expression.hpp"
#include "interpreter/expressions/callback_function_expression.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/utils.hpp"

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
    FILTER,
    MAP,
    REDUCE,
    FLAT,
    FLAT_MAP,
    FOR_EACH
};

class Array {
public:
    Storage::DataWrapper callMethod(std::string method, Expr *caller, const std::vector<std::unique_ptr<Expr>> args, std::vector<std::shared_ptr<Storage>> storage);

private:
    inline static const std::unordered_map<std::string, ArrayMethod> stringToEnumMap = {
        {"length", ArrayMethod::LENGTH},
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
        {"filter", ArrayMethod::FILTER},
        {"map", ArrayMethod::MAP},
        {"reduce", ArrayMethod::REDUCE},
        {"flat", ArrayMethod::FLAT},
        {"flatMap", ArrayMethod::FLAT_MAP},
        {"forEach", ArrayMethod::FOR_EACH}
    };

    Storage::DataWrapper length(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper push(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper pop(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper shift(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper unshift(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper splice(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper reverse(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper sort(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper fill(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper concat(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper slice(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper includes(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper indexOf(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper lastIndexOf(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper join(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper every(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper some(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper find(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper findIndex(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper filter(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper map(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper reduce(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper flat(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper flatMap(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
    Storage::DataWrapper forEach(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage);
};

#endif // ARRAY_HPP
