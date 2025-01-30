#include "interpreter/storage.hpp"

Storage::Data::Data() : _int(0) {}
Storage::Data::Data(int value) : _int(value) {}
Storage::Data::Data(double value) : _double(value) {}
Storage::Data::Data(bool value) : _bool(value) {}
Storage::Data::Data(char value) : _char(value) {}
Storage::Data::Data(std::string *value) : _string(value) {}
Storage::Data::Data(std::vector<DataWrapper> *value) : _array(value) {}
Storage::Data::Data(std::map<std::string, DataWrapper> *value)
    : _object(value) {}
Storage::Data::Data(FunctionDeclaration *value) : _function(value) {}
Storage::Data::Data(CallbackFunctionExpr *value) : _callbackFunction(value) {}
Storage::Data::~Data() {}

Storage::DataWrapper::DataWrapper()
    : wrapperType(WrapperType::VARIABLE), dataType(DataType::INTEGER), data() {}

Storage::DataWrapper::DataWrapper(WrapperType st, DataType dt,
                                  const Data &value)
    : wrapperType(st), dataType(dt) {
  if ((dt == DataType::STRING || dt == DataType::HEXCODE) && value._string) {
    data._string = new std::string(*value._string);
  } else if (dt == DataType::FUNCTION && value._function) {
    data._function = value._function;
  } else if (dt == DataType::CALLBACK_FUNCTION && value._callbackFunction) {
    data._callbackFunction = value._callbackFunction;
  } else {
    data = value;
  }
}

Storage::DataWrapper::DataWrapper(const DataWrapper &other)
    : wrapperType(other.wrapperType), dataType(other.dataType) {
  if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
    data._string = new std::string(*other.data._string);
  } else if (dataType == DataType::FUNCTION && other.data._function) {
    data._function = other.data._function;
  } else if (dataType == DataType::CALLBACK_FUNCTION && other.data._callbackFunction) {
    data._callbackFunction = other.data._callbackFunction;
  } else {
    data = other.data;
  }
}

Storage::DataWrapper::DataWrapper(DataWrapper &&other) noexcept
    : wrapperType(other.wrapperType), dataType(other.dataType),
      data(other.data) {
  other.data._string = nullptr;
}

Storage::DataWrapper &
Storage::DataWrapper::operator=(const DataWrapper &other) {
  if (this != &other) {
    clear();
    wrapperType = other.wrapperType;
    dataType = other.dataType;
    if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
      data._string = new std::string(*other.data._string);
    } else {
      data = other.data;
    }
  }
  return *this;
}

Storage::DataWrapper &
Storage::DataWrapper::operator=(DataWrapper &&other) noexcept {
  if (this != &other) {
    clear();
    wrapperType = other.wrapperType;
    dataType = other.dataType;
    data = other.data;
    other.data._string = nullptr;
  }
  return *this;
}

Storage::DataWrapper::~DataWrapper() { clear(); }

void Storage::DataWrapper::clear() {
  if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
    delete data._string;
    data._string = nullptr;
  }
}

bool Storage::DataWrapper::equals(const DataWrapper &other) const {
  if (dataType != other.dataType) {
    return false;
  }
  switch (dataType) {
  case DataType::INTEGER:
    return data._int == other.data._int;
  case DataType::DOUBLE:
    return data._double == other.data._double;
  case DataType::BOOLEAN:
    return data._bool == other.data._bool;
  case DataType::CHAR:
    return data._char == other.data._char;
  case DataType::STRING:
  case DataType::HEXCODE:
    return *data._string == *other.data._string;
  case DataType::ARRAY:
    if (data._array->size() != other.data._array->size()) {
      return false;
    }
    for (size_t i = 0; i < data._array->size(); ++i) {
      if (!data._array->at(i).equals(other.data._array->at(i))) {
        return false;
      }
    }
    return true;
  case DataType::OBJECT:
    if (data._object->size() != other.data._object->size()) {
      return false;
    }
    for (const auto &entry : *data._object) {
      if (!entry.second.equals(other.data._object->at(entry.first))) {
        return false;
      }
    }
    return true;
  case DataType::FUNCTION:
    return data._function == other.data._function;
  case DataType::CALLBACK_FUNCTION:
    return data._callbackFunction == other.data._callbackFunction;
  case DataType::_NULL:
    return true;
  }
  return false;
}

void Storage::setValue(const std::string &name, DataWrapper dataWrapper) {
  if (storage.find(name) != storage.end()) {
    throw std::invalid_argument("Identifier '" + name +
                                " 'is already defined!");
  }
  storage[name] = dataWrapper;
}

void Storage::updateValue(const std::string &name, DataWrapper dataWrapper) {
  if (storage.find(name) != storage.end()) {
    storage[name] = dataWrapper;
  } else {
    throw std::invalid_argument("Undefined identifier: " + name);
  }
}

bool Storage::exists(const std::string &name) const {
  return storage.find(name) != storage.end();
}

Storage::DataWrapper &Storage::getEntry(const std::string &name) {
  if (storage.find(name) != storage.end()) {
    return storage.at(name);
  }
  throw std::invalid_argument("Undefined identifier: " + name);
}
