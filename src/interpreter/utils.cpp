#include "interpreter/utils.hpp"

Storage::DataWrapper _integer(int value) {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::INTEGER, value);
}

Storage::DataWrapper _double(double value) {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::DOUBLE, value);
}

Storage::DataWrapper _boolean(bool value) {
  return Storage::DataWrapper(Storage::WrapperType::VALUE,
                              Storage::DataType::BOOLEAN, value);
}

bool checkTrueishness(const std::unique_ptr<Expr> &expr,
                      std::shared_ptr<Storage> storage) {
  Storage::DataWrapper datawrapper = Expression(expr.get(), storage).execute();
  switch (datawrapper.dataType) {
  case Storage::DataType::BOOLEAN:
    return datawrapper.data._bool;
  case Storage::DataType::INTEGER:
    return datawrapper.data._int != 0;
  case Storage::DataType::DOUBLE:
    return datawrapper.data._double != 0.0;
  case Storage::DataType::STRING:
  case Storage::DataType::HEXCODE:
    return !datawrapper.data._string->empty();
  case Storage::DataType::CHAR:
    return datawrapper.data._char != '\0';
  case Storage::DataType::_NULL:
    return false;
  default:
    throw std::invalid_argument("Invalid truthiness expression!");
  }
}

bool checkEquality(Storage::DataWrapper left, Storage::DataWrapper right,
                   bool equality) {
  switch (left.dataType) {
  case Storage::DataType::BOOLEAN:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
      return equality == (left.data._bool == right.data._bool);
    case Storage::DataType::INTEGER:
      if (right.data._int != 0 && right.data._int != 1) {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == (left.data._bool == (right.data._int == 1));
    case Storage::DataType::DOUBLE:
      if (right.data._double != 0.0 && right.data._double != 1.0) {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == (left.data._bool == (right.data._double == 1.0));
    case Storage::DataType::CHAR:
      if (right.data._char != '0' && right.data._char != '1') {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == (left.data._bool == (right.data._char == '1'));
    case Storage::DataType::STRING:
      if (*right.data._string != "0" && *right.data._string != "1" &&
          toLowerCase(*right.data._string) != "false" &&
          toLowerCase(*right.data._string) != "true") {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality ==
             (left.data._bool == (*right.data._string == "1" ||
                                  toLowerCase(*right.data._string) == "true"));
    case Storage::DataType::HEXCODE:
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
      if (left.data._int != 0 && left.data._int != 1) {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == ((left.data._int == 1) == right.data._bool);
    case Storage::DataType::INTEGER:
      return equality == (left.data._int == right.data._int);
    case Storage::DataType::DOUBLE:
      return equality == (left.data._int == right.data._double);
    case Storage::DataType::CHAR:
      return equality == (left.data._int == right.data._char);
    case Storage::DataType::STRING:
      return equality ==
             (std::to_string(left.data._int) == *right.data._string);
    case Storage::DataType::HEXCODE:
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
      if (left.data._double != 0.0 && left.data._double != 1.0) {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == ((left.data._double == 1.0) == right.data._bool);
    case Storage::DataType::INTEGER:
      return equality == (left.data._double == right.data._int);
    case Storage::DataType::DOUBLE:
      return equality == (left.data._double == right.data._double);
    case Storage::DataType::CHAR:
      return equality == (left.data._double == right.data._char);
    case Storage::DataType::STRING:
      return equality ==
             (std::to_string(left.data._double) == *right.data._string);
    case Storage::DataType::HEXCODE:
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
      if (left.data._char != '0' && left.data._char != '1') {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality == ((left.data._char == '1') == right.data._bool);
    case Storage::DataType::INTEGER:
      return equality == (left.data._char == right.data._int);
    case Storage::DataType::DOUBLE:
      return equality == (left.data._char == right.data._double);
    case Storage::DataType::CHAR:
      return equality == (left.data._char == right.data._char);
    case Storage::DataType::STRING:
      return equality ==
             (std::string(1, left.data._char) == *right.data._string);
    case Storage::DataType::HEXCODE:
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::STRING:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
      if (*left.data._string != "0" && *left.data._string != "1" &&
          toLowerCase(*left.data._string) != "false" &&
          toLowerCase(*left.data._string) != "true") {
        throw std::invalid_argument("Invalid equality expression!");
      }
      return equality ==
             ((*left.data._string == "1" ||
               toLowerCase(*left.data._string) == "true") == right.data._bool);
    case Storage::DataType::INTEGER:
      return equality ==
             (*left.data._string == std::to_string(right.data._int));
    case Storage::DataType::DOUBLE:
      return equality ==
             (*left.data._string == std::to_string(right.data._double));
    case Storage::DataType::CHAR:
      return equality ==
             (*left.data._string == std::string(1, right.data._char));
    case Storage::DataType::STRING:
    case Storage::DataType::HEXCODE:
      return equality == (*left.data._string == *right.data._string);
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::HEXCODE:
    switch (right.dataType) {
    case Storage::DataType::STRING:
    case Storage::DataType::HEXCODE:
      return equality == (left.data._string == right.data._string);
    case Storage::DataType::BOOLEAN:
    case Storage::DataType::INTEGER:
    case Storage::DataType::DOUBLE:
    case Storage::DataType::CHAR:
    case Storage::DataType::_NULL:
      return equality == false;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  case Storage::DataType::_NULL:
    switch (right.dataType) {
    case Storage::DataType::BOOLEAN:
    case Storage::DataType::INTEGER:
    case Storage::DataType::DOUBLE:
    case Storage::DataType::CHAR:
    case Storage::DataType::STRING:
    case Storage::DataType::HEXCODE:
      return equality == false;
    case Storage::DataType::_NULL:
      return equality == true;
    default:
      throw std::invalid_argument("Invalid equality expression!");
    }

  default:
    throw std::invalid_argument("Invalid equality expression!");
  }
}

bool checkGreater(Storage::DataWrapper left, Storage::DataWrapper right) {
  std::regex int_regex("^-?\\d+$");
  std::regex double_regex("^-?\\d+(\\.\\d+)?([eE][+-]?\\d+)?$");
  switch (left.dataType) {
  case Storage::DataType::INTEGER:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return left.data._int > right.data._int;
    case Storage::DataType::DOUBLE:
      return left.data._int > right.data._double;
    case Storage::DataType::CHAR:
      return left.data._int > right.data._char;
    case Storage::DataType::STRING:
      if (!std::regex_match(*right.data._string, int_regex)) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return left.data._int > std::stoi(*right.data._string);
    default:
      throw std::invalid_argument("Invalid greater expression!");
    }

  case Storage::DataType::DOUBLE:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return left.data._double > right.data._int;
    case Storage::DataType::DOUBLE:
      return left.data._double > right.data._double;
    case Storage::DataType::CHAR:
      return left.data._double > right.data._char;
    case Storage::DataType::STRING:
      if (!std::regex_match(*right.data._string, double_regex)) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return left.data._double > std::stod(*right.data._string);
    default:
      throw std::invalid_argument("Invalid greater expression!");
    }

  case Storage::DataType::CHAR:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      return left.data._char > right.data._int;
    case Storage::DataType::DOUBLE:
      return left.data._char > right.data._double;
    case Storage::DataType::CHAR:
      return left.data._char > right.data._char;
    case Storage::DataType::STRING:
      if (right.data._string->size() != 1) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return left.data._char > right.data._string->at(0);
    default:
      throw std::invalid_argument("Invalid greater expression!");
    }

  case Storage::DataType::STRING:
    switch (right.dataType) {
    case Storage::DataType::INTEGER:
      if (!std::regex_match(*left.data._string, int_regex)) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return std::stoi(*left.data._string) > right.data._int;
    case Storage::DataType::DOUBLE:
      if (!std::regex_match(*left.data._string, double_regex)) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return std::stod(*left.data._string) > right.data._double;
    case Storage::DataType::CHAR:
      if (left.data._string->size() != 1) {
        throw std::invalid_argument("Invalid greater expression!");
      }
      return left.data._string->at(0) > right.data._char;
    case Storage::DataType::STRING:
    case Storage::DataType::HEXCODE:
      return *left.data._string > *right.data._string;
    default:
      throw std::invalid_argument("Invalid greater expression!");
    }

  case Storage::DataType::HEXCODE:
    switch (right.dataType) {
    case Storage::DataType::STRING:
    case Storage::DataType::HEXCODE:
      return left.data._string > right.data._string;
    default:
      throw std::invalid_argument("Invalid greater expression!");
    }

  default:
    throw std::invalid_argument("Invalid greater expression!");
  }
}

std::string toLowerCase(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}