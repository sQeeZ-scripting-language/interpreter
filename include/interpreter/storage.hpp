#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <any>
#include <unordered_map>
#include <string>
#include <stdexcept>

class Storage {
public:
    enum class StorageType {
        VARIABLE,
        CONSTANT,
        FUNCTION
    };

    struct StorageEntry {
        std::any value;
        StorageType type;

        StorageEntry(std::any val, StorageType t) 
            : value(std::move(val)), type(t) {}
    };

    template <typename T>
    void setVariable(const std::string& name, T value) {
        store.emplace(name, StorageEntry(std::any(value), StorageType::VARIABLE));
    }

    template <typename T>
    void setConstant(const std::string& name, T value) {
        store.emplace(name, StorageEntry(std::any(value), StorageType::VARIABLE));
    }

    template <typename T>
    void setFunction(const std::string& name, T value) {
        store.emplace(name, StorageEntry(std::any(value), StorageType::VARIABLE));
    }

    template <typename T>
    T get(const std::string& name) const {
        auto it = store.find(name);
        if (it != store.end()) {
            return std::any_cast<T>(it->second.value);
        }
        throw std::invalid_argument("Identifier '" + name + "' not found");
    }

    void update(const std::string& name, const std::any& value) {
        auto it = store.find(name);
        if (it != store.end()) {
            switch (it->second.type)
            {
            case StorageType::VARIABLE:
                it->second.value = value;
                break;
            
            case StorageType::CONSTANT:
                throw std::logic_error("Cannot update constant '" + name + "'");
                break;

            case StorageType::FUNCTION:
                throw std::logic_error("Cannot redefine function '" + name + "'");
                break;

            default:
                throw std::runtime_error("Unknown storage type");
                break;
            }
        } else {
            throw std::invalid_argument("Identifier '" + name + "' not found");
        }
    }

    bool exists(const std::string& name) const {
        return store.find(name) != store.end();
    }

    StorageType getType(const std::string& name) const {
        auto it = store.find(name);
        if (it != store.end()) {
            return it->second.type;
        }
        throw std::invalid_argument("Identifier '" + name + "' not found");
    }

private:
    std::unordered_map<std::string, StorageEntry> store;
};

#endif // STORAGE_HPP
