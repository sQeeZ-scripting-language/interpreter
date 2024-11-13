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
        CONSTANT
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

        // Default constructor
        StorageEntry() 
            : storageType(StorageType::VARIABLE), 
            dataType(DataType::INTEGER), 
            data() {}

        // Parameterized constructor
        StorageEntry(StorageType st, DataType dt, const Data& value) 
            : storageType(st), dataType(dt) {
            if ((dt == DataType::STRING || dt == DataType::HEXCODE) && value._string) {
                data._string = new std::string(*value._string);
            } else {
                data = value;
            }
        }

        // Copy constructor
        StorageEntry(const StorageEntry& other) 
            : storageType(other.storageType), dataType(other.dataType) {
            if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
                data._string = new std::string(*other.data._string);
            } else {
                data = other.data;
            }
        }

        // Move constructor
        StorageEntry(StorageEntry&& other) noexcept 
            : storageType(other.storageType), dataType(other.dataType), data(other.data) {
            other.data._string = nullptr;
        }

        // Copy assignment operator
        StorageEntry& operator=(const StorageEntry& other) {
            if (this != &other) {
                clear();

                storageType = other.storageType;
                dataType = other.dataType;

                if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
                    data._string = new std::string(*other.data._string);
                } else {
                    data = other.data;
                }
            }
            return *this;
        }

        // Move assignment operator
        StorageEntry& operator=(StorageEntry&& other) noexcept {
            if (this != &other) {
                clear();
                storageType = other.storageType;
                dataType = other.dataType;
                data = other.data;
                other.data._string = nullptr;
            }
            return *this;
        }

        // Destructor
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

    void setValue(const std::string& name, StorageType storageType, Expr* expression) {
        if (storage.find(name) != storage.end()) {
            throw std::invalid_argument("Identifier '" + name + " 'is already defined!");
        }
        storeValue(name, storageType, expression);
    }

    void updateValue(const std::string& name, Expr* expression) {
        if (storage.find(name) != storage.end()) {
            storeValue(name, storage.at(name).storageType, expression);
        } else {
            throw std::invalid_argument("Undefined identifier: " + name);
        }
    }

    bool exists(const std::string& name) const {
        return storage.find(name) != storage.end();
    }
    
    StorageEntry& getEntry(const std::string& name) {
        if (storage.find(name) != storage.end()) {
            return storage.at(name);
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    StorageType getStorageType(const std::string& name) {
        if (storage.find(name) != storage.end()) {
            return storage.at(name).storageType;
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    DataType getDataType(const std::string& name) {
                if (storage.find(name) != storage.end()) {
            return storage.at(name).dataType;
        }
        throw std::invalid_argument("Undefined identifier: " + name);
    }

    std::any getValue(const std::string& name) {
        if (storage.find(name) != storage.end()) {
            auto& entry = storage.at(name);
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

    void storeFunction(const std::string& name, std::shared_ptr<FunctionDeclaration> function) {
        if (functions.find(name) != functions.end()) {
            throw std::invalid_argument("Function '" + name + "' is already defined!");
        }
        functions[name] = function;
    }

private:
    std::unordered_map<std::string, StorageEntry> storage;
    std::unordered_map<std::string, std::shared_ptr<FunctionDeclaration>> functions;

    void storeValue(const std::string& name, StorageType storageType, Expr* expression) {
        if (auto expr = dynamic_cast<IntegerLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::INTEGER, expr->value);
        } else if (auto expr = dynamic_cast<DoubleLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::DOUBLE, expr->value);
        } else if (auto expr = dynamic_cast<BooleanLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::BOOLEAN, expr->value);
        } else if (auto expr = dynamic_cast<CharLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::CHAR, expr->value);
        } else if (auto expr = dynamic_cast<StringLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::STRING, new std::string(expr->value));
        } else if (auto expr = dynamic_cast<HexCodeLiteral*>(expression)) {
            storage[name] = StorageEntry(storageType, DataType::HEXCODE, new std::string(expr->value));
        } else {
            throw std::invalid_argument("Unknown literal type!");
        }
    }
};

#endif // STORAGE_HPP
