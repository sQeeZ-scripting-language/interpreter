#include "interpreter/statements/log_statement.hpp"

LogStatement::LogStatement(LogStmt *logNode,
                           std::vector<std::shared_ptr<Storage>> storage)
    : logNode(logNode), storage(std::move(storage)) {}

void LogStatement::execute() {
  if (logNode->logType.tag != Token::TypeTag::LOG) {
    throw std::logic_error("Expected log token.");
  }
  if (!logNode->message) {
    return;
  }

  std::string printableValue = getPrintableValue(
      Expression(dynamic_cast<Expr *>(logNode->message.get()), storage)
          .execute());

  switch (logNode->logType.type.logToken) {
  case LogToken::BASIC:
    std::cout << printableValue << std::endl;
    break;

  case LogToken::COLORED:
    int r, g, b;
    if (auto *hexCode = dynamic_cast<HexCodeLiteral *>(logNode->color.get())) {
      hexToRGB(hexCode->value, r, g, b);
      std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m"
                << printableValue << "\033[0m" << std::endl;
    } else {
      throw std::invalid_argument("Expected hex code for colored log message.");
    }
    break;

  case LogToken::WARN:
    std::cout << "\033[33m" << printableValue << "\033[0m" << std::endl;
    break;

  case LogToken::ERROR:
    std::cout << "\033[31m" << printableValue << "\033[0m" << std::endl;
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