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
  enum class WrapperType { VALUE, VARIABLE, CONSTANT };
  enum DataType { INTEGER, DOUBLE, BOOLEAN, CHAR, STRING, HEXCODE, _NULL };

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

  struct DataWrapper {
    WrapperType wrapperType;
    DataType dataType;
    Data data;

    DataWrapper();
    DataWrapper(WrapperType st, DataType dt, const Data &value);
    DataWrapper(const DataWrapper &other);
    DataWrapper(DataWrapper &&other) noexcept;
    DataWrapper &operator=(const DataWrapper &other);
    DataWrapper &operator=(DataWrapper &&other) noexcept;
    ~DataWrapper();

    void clear();
  };

  void setValue(const std::string &name, DataWrapper dataWrapper);
  void updateValue(const std::string &name, DataWrapper dataWrapper);
  bool exists(const std::string &name) const;
  bool functionExists(const std::string &name) const;
  DataWrapper &getEntry(const std::string &name);
  void storeFunction(const std::string &name,
                     std::shared_ptr<FunctionDeclaration> function);

private:
  std::unordered_map<std::string, DataWrapper> storage;
  std::unordered_map<std::string, std::shared_ptr<FunctionDeclaration>>
      functions;
};

#endif // STORAGE_HPP
