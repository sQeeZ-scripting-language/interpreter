#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <any>
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <typeinfo>

class Storage {
public:
    enum class StorageType {
        VARIABLE,
        CONSTANT,
        FUNCTION
    };

    struct StorageEntry {
        std::shared_ptr<std::any> value;
        StorageType type;

        StorageEntry(std::any val, StorageType t) 
            : value(std::make_shared<std::any>(std::move(val))), type(t) {}
    };

    template <typename T>
    void setVariable(const std::string& name, T value) {
        store[name] = Entry(value, Type::VARIABLE);
    }

    template <typename T>
    void setConstant(const std::string& name, T value) {
        store[name] = Entry(value, Type::CONSTANT);
    }

    template <typename T>
    void setFunction(const std::string& name, T value) {
        store[name] = Entry(value, Type::FUNCTION);
    }

    template <typename T>
    T get(const std::string& name) const {
        if (exists(name)) {
            return std::any_cast<T>(*(it->second.value));
        }
        throw std::runtime_error("Identifier '" + name + "' not found");
    }

    void update(const std::string& name, const std::any& value) {
        if(getType(name) == StorageType::VARIABLE) {
            store[name].value = std::make_shared<std::any>(value);
        } else {
            throw std::runtime_error("Cannot update constant '" + name + "'");
        }
    }

    bool exists(const std::string& name) const {
        return store.find(name) != store.end();
    }

    StorageType getType(const std::string& name) const {
        if (exists(name)) {
            return store.find(name)->second.type;
        }
        throw std::runtime_error("Identifier '" + name + "' not found");
    }

private:
    std::unordered_map<std::string, StorageEntry> store;
};

#endif // STORAGE_HPP
