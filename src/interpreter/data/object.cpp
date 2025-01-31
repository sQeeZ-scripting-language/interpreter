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
    return Storage::DataWrapper();
}

Storage::DataWrapper Object::keys(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Object::values(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Object::entries(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}

Storage::DataWrapper Object::get(std::string method, Expr *caller, Storage::DataWrapper callerValue, const std::vector<std::unique_ptr<Expr>>& args, std::vector<std::shared_ptr<Storage>> storage) {
    return Storage::DataWrapper();
}
