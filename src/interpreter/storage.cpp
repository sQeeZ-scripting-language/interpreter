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
Storage::Data::~Data() {}

Storage::DataWrapper::DataWrapper()
    : wrapperType(WrapperType::VARIABLE), dataType(DataType::INTEGER), data() {}

Storage::DataWrapper::DataWrapper(WrapperType st, DataType dt,
                                  const Data &value)
    : wrapperType(st), dataType(dt) {
  if ((dt == DataType::STRING || dt == DataType::HEXCODE) && value._string) {
    data._string = new std::string(*value._string);
  } else {
    data = value;
  }
}

Storage::DataWrapper::DataWrapper(const DataWrapper &other)
    : wrapperType(other.wrapperType), dataType(other.dataType) {
  if (dataType == DataType::STRING || dataType == DataType::HEXCODE) {
    data._string = new std::string(*other.data._string);
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

void Storage::setValue(const std::string &name, DataWrapper dataWrapper) {
  if (storage.find(name) != storage.end()) {
    throw std::invalid_argument("Identifier '" + name +
                                " 'is already defined!");
  }
  dataWrapper.wrapperType = WrapperType::VARIABLE;
  storage[name] = dataWrapper;
}

void Storage::updateValue(const std::string &name, DataWrapper dataWrapper) {
  if (storage.find(name) != storage.end()) {
    dataWrapper.wrapperType = WrapperType::VARIABLE;
    storage[name] = dataWrapper;
  } else {
    throw std::invalid_argument("Undefined identifier: " + name);
  }
}

bool Storage::exists(const std::string &name) const {
  return storage.find(name) != storage.end();
}

bool Storage::functionExists(const std::string &name) const {
  return functions.find(name) != functions.end();
}

Storage::DataWrapper &Storage::getEntry(const std::string &name) {
  if (storage.find(name) != storage.end()) {
    return storage.at(name);
  }
  throw std::invalid_argument("Undefined identifier: " + name);
}

void Storage::storeFunction(const std::string &name,
                            std::shared_ptr<FunctionDeclaration> function) {
  if (functions.find(name) != functions.end()) {
    throw std::invalid_argument("Function '" + name + "' is already defined!");
  }
  functions[name] = function;
}
