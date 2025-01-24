#include "interpreter/data/array.hpp"

Storage::DataWrapper Array::callMethod(std::string method, Expr *caller, const std::vector<std::unique_ptr<Expr>> args, std::vector<std::shared_ptr<Storage>> storage) {;
    Storage::DataWrapper callerValue = Expression(caller, storage).execute();
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    switch (stringToEnumMap.at(method)) {
        case ArrayMethod::PUSH:
            if (args.size() != 1) {
                throw std::logic_error("Invalid number of arguments!");
            }
            callerValue.data._array->push_back(Expression(args[0].get(), storage).execute());
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, static_cast<int>(callerValue.data._array->size()));
        case ArrayMethod::POP:
            if (args.size() != 0) {
                throw std::logic_error("Invalid number of arguments!");
            }
            if (callerValue.data._array->empty()) {
                return tmpValue;
            }
            tmpValue = callerValue.data._array->back();
            callerValue.data._array->pop_back();
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return tmpValue;
        case ArrayMethod::SHIFT:
        case ArrayMethod::UNSHIFT:
        case ArrayMethod::SPLICE:
        case ArrayMethod::REVERSE:
        case ArrayMethod::SORT:
        case ArrayMethod::FILL:
        case ArrayMethod::CONCAT:
        case ArrayMethod::SLICE:
        case ArrayMethod::INCLUDES:
        case ArrayMethod::INDEX_OF:
        case ArrayMethod::LAST_INDEX_OF:
        case ArrayMethod::JOIN:
        case ArrayMethod::EVERY:
        case ArrayMethod::SOME:
        case ArrayMethod::FIND:
        case ArrayMethod::FIND_INDEX:
        case ArrayMethod::FILTER:
        case ArrayMethod::MAP:
        case ArrayMethod::REDUCE:
        case ArrayMethod::FLAT:
        case ArrayMethod::FLAT_MAP:
        case ArrayMethod::FOR_EACH:
        default:
            throw std::runtime_error("Invalid array method!");
    }
}