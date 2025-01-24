#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <unordered_map>
#include <string>
#include "interpreter/storage.hpp"
#include "interpreter/expressions/expression.hpp"
#include "parser/ast_nodes.hpp"
#include "interpreter/utils.hpp"

enum class ArrayMethod {
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
};

#endif // ARRAY_HPP
