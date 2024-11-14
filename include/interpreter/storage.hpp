#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "parser/ast_nodes.hpp"
#include <any>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class Storage {
public:
  enum class StorageType { VARIABLE, CONSTANT };
  enum DataType { INTEGER, DOUBLE, BOOLEAN, CHAR, STRING, HEXCODE };

  union Data {
    int _int;
    double _double;
    bool _bool;
    char _char;
    std::string *_string;

    Data();
    Data(int value);
    Data(double value);
    Data(bool value);
    Data(char value);
    Data(std::string *value);
    ~Data();
  };

  struct StorageEntry {
    StorageType storageType;
    DataType dataType;
    Data data;

    StorageEntry();
    StorageEntry(StorageType st, DataType dt, const Data &value);
    StorageEntry(const StorageEntry &other);
    StorageEntry(StorageEntry &&other) noexcept;
    StorageEntry &operator=(const StorageEntry &other);
    StorageEntry &operator=(StorageEntry &&other) noexcept;
    ~StorageEntry();

    void clear();
  };

  void setValue(const std::string &name, StorageType storageType,
                Expr *expression);
  void updateValue(const std::string &name, Expr *expression);
  bool exists(const std::string &name) const;
  StorageEntry &getEntry(const std::string &name);
  StorageType getStorageType(const std::string &name);
  DataType getDataType(const std::string &name);
  std::any getValue(const std::string &name);
  void storeFunction(const std::string &name,
                     std::shared_ptr<FunctionDeclaration> function);

private:
  std::unordered_map<std::string, StorageEntry> storage;
  std::unordered_map<std::string, std::shared_ptr<FunctionDeclaration>>
      functions;

  void storeValue(const std::string &name, StorageType storageType,
                  Expr *expression);
};

#endif // STORAGE_HPP
