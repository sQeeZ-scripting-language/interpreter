#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <any>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>

class Storage {
public:
    enum class StorageType {
        VARIABLE,
        CONSTANT,
        FUNCTION
    };

    enum DataType {
        INTEGER,
        DOUBLE,
        BOOLEAN,
        CHAR,
        STRING,
        HEXCODE
    };

    union Data {
        int _int;
        double _double;
        bool _bool;
        char _char;
        std::string* _string;

        Data() : _int(0) {}
        Data(int value) : _int(value) {}
        Data(double value) : _double(value) {}
        Data(bool value) : _bool(value) {}
        Data(char value) : _char(value) {}
        Data(std::string* value) : _string(value) {}

        ~Data() {}
    };

    struct StorageEntry {
        StorageType storageType;
        DataType dataType;
        Data data;

        StorageEntry() 
            : storageType(StorageType::VARIABLE), 
            dataType(DataType::INTEGER),
            data() {}

        StorageEntry(StorageType st, DataType dt, const Data& value) 
            : storageType(st), dataType(dt) {
            if ((dt == DataType::STRING || dt == DataType::HEXCODE) && value._string) {
                data._string = new std::string(*value._string);  // Deep copy for strings
            } else {
                data = value;
            }
        }

        ~StorageEntry() {
            clear();
        }

        void clear() {
            if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
                delete data._string;
                data._string = nullptr;
            }
        }
    };

    void setValue(const std::string& name, StorageType storageType, DataType dataType, const Data& value) {
        if (store.find(name) != store.end()) {
            store[name].clear();
        }
        store[name] = StorageEntry(storageType, dataType, value);
    }

    bool exists(const std::string& name) const {
        return store.find(name) != store.end();
    }
    
    StorageEntry& getEntry(const std::string& name) {
        if (store.find(name) != store.end()) {
            return store.at(name);
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    StorageType getStorageType(const std::string& name) {
        if (store.find(name) != store.end()) {
            return store.at(name).storageType;
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    DataType getDataType(const std::string& name) {
                if (store.find(name) != store.end()) {
            return store.at(name).dataType;
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    std::any getValue(const std::string& name) {
        if (store.find(name) != store.end()) {
            auto& entry = store.at(name);
            switch (entry.dataType) {
            case DataType::INTEGER:
                return entry.data._int;
            case DataType::DOUBLE:
                return entry.data._double;
            case DataType::BOOLEAN:
                return entry.data._bool;
            case DataType::CHAR:
                return entry.data._char;
            case DataType::STRING:
            case DataType::HEXCODE:
                return *(entry.data._string);
            default:
                throw std::invalid_argument("Unknown data type!");
            }
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

private:
    std::unordered_map<std::string, StorageEntry> store;
};

#endif // STORAGE_HPP
