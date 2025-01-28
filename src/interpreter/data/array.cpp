#include "interpreter/data/array.hpp"

Storage::DataWrapper Array::callMethod(std::string method, Expr *caller, const std::vector<std::unique_ptr<Expr>> args, std::vector<std::shared_ptr<Storage>> storage) {;
    Storage::DataWrapper callerValue = Expression(caller, storage).execute();
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    std::vector<Storage::DataWrapper> tmpElements, tmpDeletedElements;
    int start, end, count;

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
            if (args.size() != 0) {
                throw std::logic_error("Invalid number of arguments!");
            }
            if (callerValue.data._array->empty()) {
                return tmpValue;
            }
            tmpValue = callerValue.data._array->front();
            callerValue.data._array->erase(callerValue.data._array->begin());
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return tmpValue;
        case ArrayMethod::UNSHIFT:
            if (args.size() != 1) {
                throw std::logic_error("Invalid number of arguments!");
            }
            callerValue.data._array->insert(callerValue.data._array->begin(), Expression(args[0].get(), storage).execute());
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, static_cast<int>(callerValue.data._array->size()));
        case ArrayMethod::SPLICE:
            if (args.size() < 2 || args.size() > 3) {
                throw std::logic_error("Invalid number of arguments!");
            }
            if (callerValue.data._array->empty()) {
                return tmpValue;
            }
            if (args[0].get()->kind != NodeType::IntegerLiteral || args[1].get()->kind != NodeType::IntegerLiteral) {
                throw std::logic_error("Invalid arguments!");
            }
            start = Expression(args[0].get(), storage).execute().data._int;
            count = Expression(args[1].get(), storage).execute().data._int;
            
            if (args.size() == 3) {
                tmpElements = *(Expression(args[2].get(), storage).execute().data._array);
            }

            if (start < 0) {
                start = static_cast<int>(callerValue.data._array->size()) + start;
            }
            if (start < 0) {
                start = 0;
            }
            if (count < 0) {
                count = 0;
            }
            if (start > static_cast<int>(callerValue.data._array->size())) {
                start = static_cast<int>(callerValue.data._array->size());
            }
            if (count > static_cast<int>(callerValue.data._array->size()) - start) {
                count = static_cast<int>(callerValue.data._array->size()) - start;
            }
            
            for (int i = 0; i < count; ++i) {
                tmpDeletedElements.push_back(callerValue.data._array->at(start + i));
            }
            callerValue.data._array->erase(callerValue.data._array->begin() + start, callerValue.data._array->begin() + start + count);
            for (int i = 0; i < static_cast<int>(tmpElements.size()); ++i) {
                callerValue.data._array->insert(callerValue.data._array->begin() + start + i, tmpElements[i]);
            }
            
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(tmpDeletedElements));
        case ArrayMethod::REVERSE:
            if (args.size() != 0) {
                throw std::logic_error("Invalid number of arguments!");
            }
            std::reverse(callerValue.data._array->begin(), callerValue.data._array->end());
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return callerValue;
        case ArrayMethod::SORT:
            break;
        case ArrayMethod::FILL:
            if (args.size() < 1 || args.size() > 3) {
                throw std::logic_error("Invalid number of arguments!");
            }
            if (callerValue.data._array->empty()) {
                return tmpValue;
            }
            if (args[0].get()->kind != NodeType::Identifier && args[0].get()->kind != NodeType::ArrayLiteral && args[0].get()->kind != NodeType::ObjectLiteral && args[0].get()->kind != NodeType::IntegerLiteral && args[0].get()->kind != NodeType::DoubleLiteral && args[0].get()->kind != NodeType::CharLiteral && args[0].get()->kind != NodeType::StringLiteral && args[0].get()->kind != NodeType::BooleanLiteral && args[0].get()->kind != NodeType::NullLiteral) {
                throw std::logic_error("Invalid arguments!");
            }
            if (args.size() >= 2 && args[1].get()->kind != NodeType::IntegerLiteral) {
                throw std::logic_error("Invalid arguments!");
            }
            if (args.size() >= 3 && args[2].get()->kind != NodeType::IntegerLiteral) {
                throw std::logic_error("Invalid arguments!");
            }
            if (args.size() == 1) {
                start = 0;
                end = static_cast<int>(callerValue.data._array->size());
            } else if (args.size() == 2) {
                start = Expression(args[1].get(), storage).execute().data._int;
                end = static_cast<int>(callerValue.data._array->size());
            } else {
                start = Expression(args[1].get(), storage).execute().data._int;
                end = Expression(args[2].get(), storage).execute().data._int;
            }
            for (int i = start; i < end; ++i) {
                callerValue.data._array->at(i) = Expression(args[0].get(), storage).execute();
            }
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return callerValue;
        case ArrayMethod::CONCAT:
            if (args.size() != 1) {
                throw std::logic_error("Invalid number of arguments!");
            }
            if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::ARRAY) {
                throw std::logic_error("Invalid arguments!");
            }
            for (int i = 0; i < static_cast<int>(Expression(args[0].get(), storage).execute().data._array->size()); ++i) {
                callerValue.data._array->push_back(Expression(args[0].get(), storage).execute().data._array->at(i));
            }
            if (auto expr = dynamic_cast<Identifier *>(caller)) {
                int keyIndex = storageKeyIndex(storage, expr->identifier.value);
                if (keyIndex == -1) {
                    throw std::logic_error("Variable not declared.");
                }
                storage[keyIndex]->updateValue(expr->identifier.value, callerValue);
            }
            return callerValue;
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