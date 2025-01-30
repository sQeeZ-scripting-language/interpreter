#include "interpreter/data/array.hpp"

Storage::DataWrapper Array::callMethod(std::string method, Expr *caller, const std::vector<std::unique_ptr<Expr>> args, std::vector<std::shared_ptr<Storage>> storage) {;
    Storage::DataWrapper callerValue = Expression(caller, storage).execute();

    switch (stringToEnumMap.at(method)) {
        case ArrayMethod::LENGTH:
            return length(method, caller, callerValue, args, storage);
        case ArrayMethod::PUSH:
            return push(method, caller, callerValue, args, storage);
        case ArrayMethod::POP:
            return pop(method, caller, callerValue, args, storage);
        case ArrayMethod::SHIFT:
            return shift(method, caller, callerValue, args, storage);
        case ArrayMethod::UNSHIFT:
            return unshift(method, caller, callerValue, args, storage);
        case ArrayMethod::SPLICE:
            return splice(method, caller, callerValue, args, storage);
        case ArrayMethod::REVERSE:
            return reverse(method, caller, callerValue, args, storage);
        case ArrayMethod::SORT:
            return sort(method, caller, callerValue, args, storage);
        case ArrayMethod::FILL:
            return fill(method, caller, callerValue, args, storage);
        case ArrayMethod::CONCAT:
            return concat(method, caller, callerValue, args, storage);
        case ArrayMethod::SLICE:
            return slice(method, caller, callerValue, args, storage);
        case ArrayMethod::INCLUDES:
            return includes(method, caller, callerValue, args, storage);
        case ArrayMethod::INDEX_OF:
            return indexOf(method, caller, callerValue, args, storage);
        case ArrayMethod::LAST_INDEX_OF:
            return lastIndexOf(method, caller, callerValue, args, storage);
        case ArrayMethod::JOIN:
            return join(method, caller, callerValue, args, storage);
        case ArrayMethod::EVERY:
            return every(method, caller, callerValue, args, storage);
        case ArrayMethod::SOME:
            return some(method, caller, callerValue, args, storage);
        case ArrayMethod::FIND:
            return find(method, caller, callerValue, args, storage);
        case ArrayMethod::FIND_INDEX:
            return findIndex(method, caller, callerValue, args, storage);
        case ArrayMethod::FILTER:
            return filter(method, caller, callerValue, args, storage);
        case ArrayMethod::MAP:
            return map(method, caller, callerValue, args, storage);
        case ArrayMethod::REDUCE:
            return reduce(method, caller, callerValue, args, storage);
        case ArrayMethod::FLAT:
            return flat(method, caller, callerValue, args, storage);
        case ArrayMethod::FLAT_MAP:
            return flatMap(method, caller, callerValue, args, storage);
        case ArrayMethod::FOR_EACH:
            return forEach(method, caller, callerValue, args, storage);
        default:
            throw std::runtime_error("Invalid array method!");
    }
}

Storage::DataWrapper Array::length(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 0) {
        throw std::logic_error("Invalid number of arguments!");
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, static_cast<int>(callerValue.data._array->size()));
}

Storage::DataWrapper Array::push(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
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
}

Storage::DataWrapper Array::pop(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
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
}

Storage::DataWrapper Array::shift(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
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
}

Storage::DataWrapper Array::unshift(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
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
}

Storage::DataWrapper Array::splice(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    std::vector<Storage::DataWrapper> tmpElements, tmpDeletedElements;
    int start, count;
    if (args.size() < 2 || args.size() > 3) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (callerValue.data._array->empty()) {
        return tmpValue;
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER || Expression(args[1].get(), storage).execute().dataType != Storage::DataType::INTEGER) {
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
}

Storage::DataWrapper Array::reverse(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
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
}

Storage::DataWrapper Array::sort(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Array::fill(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    int start, end;
    if (args.size() < 1 || args.size() > 3) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (callerValue.data._array->empty()) {
        return tmpValue;
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::ARRAY && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::BOOLEAN && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::CHAR && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::DOUBLE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::HEXCODE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::OBJECT && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::_NULL) {
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
}

Storage::DataWrapper Array::concat(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
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
}

Storage::DataWrapper Array::slice(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper tmpValue = Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    std::vector<Storage::DataWrapper> tmpElements;
    int start, end;
    if (args.size() == 0) {
        return callerValue;
    }
    if (args.size() > 2) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (args.size() >= 1 && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER) {
        throw std::logic_error("Invalid arguments!");
    }
    if (args.size() >= 2 && Expression(args[1].get(), storage).execute().dataType != Storage::DataType::INTEGER) {
        throw std::logic_error("Invalid arguments!");
    }
    if (Expression(args[0].get(), storage).execute().data._int < 0) {
        start = static_cast<int>(callerValue.data._array->size()) + Expression(args[0].get(), storage).execute().data._int;
    } else if (Expression(args[0].get(), storage).execute().data._int > static_cast<int>(callerValue.data._array->size())) {
        return tmpValue;
    } else {
        start = Expression(args[0].get(), storage).execute().data._int;
    }
    if (args.size() == 1 || Expression(args[1].get(), storage).execute().data._int > static_cast<int>(callerValue.data._array->size())) {
        end = static_cast<int>(callerValue.data._array->size());
    } else if(Expression(args[1].get(), storage).execute().data._int < 0) {
        end = static_cast<int>(callerValue.data._array->size()) + Expression(args[1].get(), storage).execute().data._int;
    } else {
        end = Expression(args[1].get(), storage).execute().data._int;
    }
    if (start >= end) {
        return tmpValue;
    }
    for (int i = start; i < end; ++i) {
        tmpElements.push_back(callerValue.data._array->at(i));
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(tmpElements));
}

Storage::DataWrapper Array::includes(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::ARRAY && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::BOOLEAN && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::CHAR && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::DOUBLE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::HEXCODE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::OBJECT && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::_NULL) {
        throw std::logic_error("Invalid arguments!");
    }
    for (int i = 0; i < callerValue.data._array->size(); ++i) {
        if (callerValue.data._array->at(i).equals(Expression(args[0].get(), storage).execute())) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, true);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, false);
}

Storage::DataWrapper Array::indexOf(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::ARRAY && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::BOOLEAN && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::CHAR && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::DOUBLE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::HEXCODE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::OBJECT && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::_NULL) {
        throw std::logic_error("Invalid arguments!");
    }
    for (int i = 0; i < callerValue.data._array->size(); ++i) {
        if (callerValue.data._array->at(i).equals(Expression(args[0].get(), storage).execute())) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, i);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, -1);
}

Storage::DataWrapper Array::lastIndexOf(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::ARRAY && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::BOOLEAN && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::CHAR && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::DOUBLE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::HEXCODE && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::INTEGER && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::OBJECT && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING && Expression(args[0].get(), storage).execute().dataType != Storage::DataType::_NULL) {
        throw std::logic_error("Invalid arguments!");
    }
    for (int i = static_cast<int>(callerValue.data._array->size()) - 1; i >= 0; --i) {
        if (callerValue.data._array->at(i).equals(Expression(args[0].get(), storage).execute())) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, i);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, -1);
}

Storage::DataWrapper Array::join(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() > 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    std::string separator = "";
    if (args.size() == 1) {
        if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING) {
            throw std::logic_error("Invalid arguments!");
        }
        separator = *(Expression(args[0].get(), storage).execute().data._string);
    }
    std::string result = "";
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        if (i != 0) {
            result += separator;
        }
        result += getPrintableValue(callerValue.data._array->at(i));
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::STRING, new std::string(result));
}

Storage::DataWrapper Array::every(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    Storage::DataWrapper callbackFunction = Expression(args[0].get(), storage).execute();
    if (callbackFunction.dataType != Storage::DataType::CALLBACK_FUNCTION) {
        throw std::logic_error("Invalid arguments!");
    }
    if (callbackFunction.data._callbackFunction->parameters.size() != 1) {
        throw std::logic_error("Invalid number of parameters!");
    }
    if (!(callbackFunction.data._callbackFunction->parameters[0].tag == Token::TypeTag::DATA && callbackFunction.data._callbackFunction->parameters[0].type.dataToken == DataToken::IDENTIFIER)) {
        throw std::logic_error("Invalid parameter!");
    }
    if (callerValue.data._array->empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, true);
    }
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
        parameterStorage->setValue(callbackFunction.data._callbackFunction->parameters[0].value, callerValue.data._array->at(i));
        Storage::DataWrapper returnValue = CallbackFunctionExpression(callbackFunction.data._callbackFunction, storage).executeBody(parameterStorage);
        if (!checkTrueishness(returnValue, storage)) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, false);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, true);
}

Storage::DataWrapper Array::some(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    Storage::DataWrapper callbackFunction = Expression(args[0].get(), storage).execute();
    if (callbackFunction.dataType != Storage::DataType::CALLBACK_FUNCTION) {
        throw std::logic_error("Invalid arguments!");
    }
    if (callbackFunction.data._callbackFunction->parameters.size() != 1) {
        throw std::logic_error("Invalid number of parameters!");
    }
    if (!(callbackFunction.data._callbackFunction->parameters[0].tag == Token::TypeTag::DATA && callbackFunction.data._callbackFunction->parameters[0].type.dataToken == DataToken::IDENTIFIER)) {
        throw std::logic_error("Invalid parameter!");
    }
    if (callerValue.data._array->empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, false);
    }
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
        parameterStorage->setValue(callbackFunction.data._callbackFunction->parameters[0].value, callerValue.data._array->at(i));
        Storage::DataWrapper returnValue = CallbackFunctionExpression(callbackFunction.data._callbackFunction, storage).executeBody(parameterStorage);
        if (checkTrueishness(returnValue, storage)) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, true);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, false);
}

Storage::DataWrapper Array::find(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    Storage::DataWrapper callbackFunction = Expression(args[0].get(), storage).execute();
    if (callbackFunction.dataType != Storage::DataType::CALLBACK_FUNCTION) {
        throw std::logic_error("Invalid arguments!");
    }
    if (callbackFunction.data._callbackFunction->parameters.size() != 1) {
        throw std::logic_error("Invalid number of parameters!");
    }
    if (!(callbackFunction.data._callbackFunction->parameters[0].tag == Token::TypeTag::DATA && callbackFunction.data._callbackFunction->parameters[0].type.dataToken == DataToken::IDENTIFIER)) {
        throw std::logic_error("Invalid parameter!");
    }
    if (callerValue.data._array->empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    }
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
        parameterStorage->setValue(callbackFunction.data._callbackFunction->parameters[0].value, callerValue.data._array->at(i));
        Storage::DataWrapper returnValue = CallbackFunctionExpression(callbackFunction.data._callbackFunction, storage).executeBody(parameterStorage);
        if (checkTrueishness(returnValue, storage)) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, callerValue.data._array->at(i).dataType, callerValue.data._array->at(i).data);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
}

Storage::DataWrapper Array::findIndex(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    Storage::DataWrapper callbackFunction = Expression(args[0].get(), storage).execute();
    if (callbackFunction.dataType != Storage::DataType::CALLBACK_FUNCTION) {
        throw std::logic_error("Invalid arguments!");
    }
    if (callbackFunction.data._callbackFunction->parameters.size() != 1) {
        throw std::logic_error("Invalid number of parameters!");
    }
    if (!(callbackFunction.data._callbackFunction->parameters[0].tag == Token::TypeTag::DATA && callbackFunction.data._callbackFunction->parameters[0].type.dataToken == DataToken::IDENTIFIER)) {
        throw std::logic_error("Invalid parameter!");
    }
    if (callerValue.data._array->empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, -1);
    }
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
        parameterStorage->setValue(callbackFunction.data._callbackFunction->parameters[0].value, callerValue.data._array->at(i));
        Storage::DataWrapper returnValue = CallbackFunctionExpression(callbackFunction.data._callbackFunction, storage).executeBody(parameterStorage);
        if (checkTrueishness(returnValue, storage)) {
            return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, i);
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::INTEGER, -1);
}

Storage::DataWrapper Array::filter(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    Storage::DataWrapper callbackFunction = Expression(args[0].get(), storage).execute();
    if (callbackFunction.dataType != Storage::DataType::CALLBACK_FUNCTION) {
        throw std::logic_error("Invalid arguments!");
    }
    if (callbackFunction.data._callbackFunction->parameters.size() != 1) {
        throw std::logic_error("Invalid number of parameters!");
    }
    if (!(callbackFunction.data._callbackFunction->parameters[0].tag == Token::TypeTag::DATA && callbackFunction.data._callbackFunction->parameters[0].type.dataToken == DataToken::IDENTIFIER)) {
        throw std::logic_error("Invalid parameter!");
    }
    if (callerValue.data._array->empty()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>());
    }
    std::vector<Storage::DataWrapper> tmpElements = std::vector<Storage::DataWrapper>();
    for (int i = 0; i < static_cast<int>(callerValue.data._array->size()); ++i) {
        std::shared_ptr<Storage> parameterStorage = std::make_shared<Storage>();
        parameterStorage->setValue(callbackFunction.data._callbackFunction->parameters[0].value, callerValue.data._array->at(i));
        Storage::DataWrapper returnValue = CallbackFunctionExpression(callbackFunction.data._callbackFunction, storage).executeBody(parameterStorage);
        if (checkTrueishness(returnValue, storage)) {
            tmpElements.push_back(callerValue.data._array->at(i));
        }
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(tmpElements));
}

Storage::DataWrapper Array::map(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Array::reduce(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Array::flat(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Array::flatMap(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Array::forEach(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}
