#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "parser/ast_nodes.hpp"
#include <any>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

class Storage {
public:
  enum class WrapperType { VALUE, VARIABLE, CONSTANT, FUNCTION };
  enum DataType {
    BOOLEAN,
    INTEGER,
    DOUBLE,
    CHAR,
    STRING,
    HEXCODE,
    ARRAY,
    OBJECT,
    FUNCTION,
    CALLBACK_FUNCTION,
    SHORT_NOTATION_OPERATION,
    _NULL
  };

  struct DataWrapper;

  union Data {
    int _int;
    double _double;
    bool _bool;
    char _char;
    std::string *_string;
    std::vector<DataWrapper> *_array;
    std::map<std::string, DataWrapper> *_object;
    FunctionDeclaration *_function;
    CallbackFunctionExpr *_callbackFunction;
    ShortOperationLiteral *_shortOperation;

    Data();
    Data(int value);
    Data(double value);
    Data(bool value);
    Data(char value);
    Data(std::string *value);
    Data(std::vector<DataWrapper> *value);
    Data(std::map<std::string, DataWrapper> *value);
    Data(FunctionDeclaration *value);
    Data(CallbackFunctionExpr *value);
    Data(ShortOperationLiteral *value);
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
    bool equals(const DataWrapper &other) const;
  };

  void setValue(const std::string &name, DataWrapper dataWrapper);
  void updateValue(const std::string &name, DataWrapper dataWrapper);
  bool exists(const std::string &name) const;
  DataWrapper &getEntry(const std::string &name);

private:
  std::unordered_map<std::string, DataWrapper> storage;
};

#endif // STORAGE_HPP
