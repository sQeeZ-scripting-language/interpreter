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
        break;

    case LogToken::WARN:
        break;

    case LogToken::ERROR:
        break;
    
    default:
        break;
    }
}