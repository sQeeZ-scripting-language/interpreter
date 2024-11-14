#include "interpreter/statements/log_statement.hpp"

LogStatement::LogStatement(LogStmt *logNode, std::shared_ptr<Storage> storage)
    : logNode(logNode), storage(std::move(storage)) {}

std::string LogStatement::getMessage() {
  if (logNode->message) {
    if (auto *strLiteral =
            dynamic_cast<StringLiteral *>(logNode->message.get())) {
      return strLiteral->value;
    } else if (auto *intLiteral =
                   dynamic_cast<IntegerLiteral *>(logNode->message.get())) {
      return std::to_string(intLiteral->value);
    } else if (auto *doubleLiteral =
                   dynamic_cast<DoubleLiteral *>(logNode->message.get())) {
      return std::to_string(doubleLiteral->value);
    } else if (auto *boolLiteral =
                   dynamic_cast<BooleanLiteral *>(logNode->message.get())) {
      return std::string(boolLiteral->value ? "true" : "false");
    } else if (auto *charLiteral =
                   dynamic_cast<CharLiteral *>(logNode->message.get())) {
      return std::string(1, charLiteral->value);
    } else if (auto *hexCodeLiteral =
                   dynamic_cast<HexCodeLiteral *>(logNode->message.get())) {
      return hexCodeLiteral->value;
    } else if (auto *identifier =
                   dynamic_cast<Identifier *>(logNode->message.get())) {
      return castStorageEntry(identifier->identifier.value);
    } else {
      throw std::logic_error("Unsupported log message type.");
    }
  } else {
    throw std::invalid_argument("No log message provided.");
  }
}

void LogStatement::execute() {
  if (logNode->logType.tag != Token::TypeTag::LOG) {
    throw std::logic_error("Expected log token.");
  }

  switch (logNode->logType.type.logToken) {
  case LogToken::BASIC:
    std::cout << getMessage() << std::endl;
    break;

  case LogToken::COLORED:
    int r, g, b;
    if (auto *hexCode = dynamic_cast<HexCodeLiteral *>(logNode->color.get())) {
      hexToRGB(hexCode->value, r, g, b);
      std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                << getMessage() << "\033[0m" << std::endl;
    } else {
      throw std::invalid_argument("Expected hex code for colored log message.");
    }
    break;

  case LogToken::WARN:
    std::cout << "\033[33m" << getMessage() << "\033[0m" << std::endl;
    break;

  case LogToken::ERROR:
    std::cout << "\033[31m" << getMessage() << "\033[0m" << std::endl;
    break;

  default:
    throw std::runtime_error("Unknown log token type.");
  }
}

void LogStatement::hexToRGB(const std::string &hex, int &r, int &g, int &b) {
  if (hex[0] == '#') {
    std::stringstream ss;
    ss << std::hex << hex.substr(1);
    unsigned int hexValue;
    ss >> hexValue;
    r = (hexValue >> 16) & 0xFF;
    g = (hexValue >> 8) & 0xFF;
    b = hexValue & 0xFF;
  } else {
    throw std::invalid_argument(
        "Invalid hex code format. Must start with '#'.");
  }
}

std::string LogStatement::castStorageEntry(const std::string &name) {
  Storage::StorageEntry entry = storage->getEntry(name);
  switch (entry.dataType) {
  case Storage::DataType::INTEGER:
    return std::to_string(entry.data._int);
  case Storage::DataType::DOUBLE:
    return std::to_string(entry.data._double);
  case Storage::DataType::BOOLEAN:
    return entry.data._bool ? "true" : "false";
  case Storage::DataType::CHAR:
    return std::string(1, entry.data._char);
  case Storage::DataType::STRING:
  case Storage::DataType::HEXCODE:
    return *(entry.data._string);
  default:
    throw std::invalid_argument("Unknown data type!");
  }
}