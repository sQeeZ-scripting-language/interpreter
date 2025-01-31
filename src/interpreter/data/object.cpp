#include "interpreter/data/object.hpp"

Storage::DataWrapper Object::callMethod(std::string method, Expr *caller, const std::vector<std::unique_ptr<Expr>> args, std::vector<std::shared_ptr<Storage>> storage) {
    Storage::DataWrapper callerValue = Expression(caller, storage).execute();

    switch (stringToEnumMap.at(method)) {
        case ObjectMethod::HAS_KEY:
            return hasKey(method, caller, callerValue, args, storage);
        case ObjectMethod::KEYS:
            return keys(method, caller, callerValue, args, storage);
        case ObjectMethod::VALUES:
            return values(method, caller, callerValue, args, storage);
        case ObjectMethod::ENTRIES:
            return entries(method, caller, callerValue, args, storage);
        case ObjectMethod::GET:
            return get(method, caller, callerValue, args, storage);
        default:
            throw std::runtime_error("Invalid object method!");
    }
}

Storage::DataWrapper Object::hasKey(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING) {
        throw std::logic_error("Invalid arguments!");
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::BOOLEAN, callerValue.data._object->find(*Expression(args[0].get(), storage).execute().data._string) != callerValue.data._object->end());
}

Storage::DataWrapper Object::keys(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 0) {
        throw std::logic_error("Invalid number of arguments!");
    }
    std::vector<Storage::DataWrapper> keys;
    for (const auto &entry : *callerValue.data._object) {
        keys.push_back(Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::STRING, new std::string(entry.first)));
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(keys));
}

Storage::DataWrapper Object::values(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 0) {
        throw std::logic_error("Invalid number of arguments!");
    }
    std::vector<Storage::DataWrapper> keys;
    for (const auto &entry : *callerValue.data._object) {
        keys.push_back(Storage::DataWrapper(Storage::WrapperType::VALUE, entry.second.dataType, entry.second.data));
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(keys));
}

Storage::DataWrapper Object::entries(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 0) {
        throw std::logic_error("Invalid number of arguments!");
    }
    std::vector<Storage::DataWrapper> keys;
    for (const auto &entry : *callerValue.data._object) {
        std::vector<Storage::DataWrapper> entryData;
        entryData.push_back(Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::STRING, new std::string(entry.first)));
        entryData.push_back(Storage::DataWrapper(Storage::WrapperType::VALUE, entry.second.dataType, entry.second.data));
        keys.push_back(Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(entryData)));
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::ARRAY, new std::vector<Storage::DataWrapper>(keys));
}

Storage::DataWrapper Object::get(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    if (args.size() != 1) {
        throw std::logic_error("Invalid number of arguments!");
    }
    if (Expression(args[0].get(), storage).execute().dataType != Storage::DataType::STRING) {
        throw std::logic_error("Invalid arguments!");
    }
    auto it = callerValue.data._object->find(*Expression(args[0].get(), storage).execute().data._string);
    if (it == callerValue.data._object->end()) {
        return Storage::DataWrapper(Storage::WrapperType::VALUE, Storage::DataType::_NULL, 0);
    }
    return Storage::DataWrapper(Storage::WrapperType::VALUE, it->second.dataType, it->second.data);
}
