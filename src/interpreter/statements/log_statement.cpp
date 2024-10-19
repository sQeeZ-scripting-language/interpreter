#include "interpreter/statements/log_statement.hpp"

LogStatement::LogStatement(LogStmt* logNode) : logNode(logNode) {}

auto LogStatement::getMessage() {
    if (logNode->message) {
        if (auto* strLiteral = dynamic_cast<StringLiteral*>(logNode->message.get())) {
            return strLiteral->value;
        } else if (auto* intLiteral = dynamic_cast<IntegerLiteral*>(logNode->message.get())) {
            return std::to_string(intLiteral->value);
        } else if (auto* doubleLiteral = dynamic_cast<DoubleLiteral*>(logNode->message.get())) {
            return std::to_string(doubleLiteral->value);
        } else {
            throw std::runtime_error("Unsupported log message type.");
        }
    } else {
        throw std::runtime_error("No log message provided.");
    }
}


void LogStatement::execute() {
    if (logNode->logType.tag != Token::TypeTag::LOG) {
        throw std::runtime_error("Expected log token.");
    }

    switch (logNode->logType.type.logToken) {
    case LogToken::BASIC:
        std::cout << getMessage() << std::endl;
        break;

    case LogToken::COLORED:
        int r, g, b;
        if (auto* hexCode = dynamic_cast<StringLiteral*>(logNode->color.get())) {
            hexToRGB(hexCode->value, r, g, b);
            std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << getMessage() << "\033[0m" << std::endl;
        } else {
            throw std::runtime_error("Expected hex code for colored log message.");
        }
        break;

    case LogToken::WARN:
        std::cout << "\033[33m" << getMessage() << "\033[0m" << std::endl;
        break;

    case LogToken::ERROR:
        std::cout << "\033[31m" << getMessage() << "\033[0m" << std::endl;
        break;
    
    default:
        break;
    }
}

void LogStatement::hexToRGB(const std::string& hex, int& r, int& g, int& b) {
    if (hex[0] == '#') {
        std::stringstream ss;
        ss << std::hex << hex.substr(1);
        unsigned int hexValue;
        ss >> hexValue;
        r = (hexValue >> 16) & 0xFF;
        g = (hexValue >> 8) & 0xFF;
        b = hexValue & 0xFF;
    }
}