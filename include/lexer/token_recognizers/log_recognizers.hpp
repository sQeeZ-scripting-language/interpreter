#ifndef LOG_RECOGNIZERS_HPP
#define LOG_RECOGNIZERS_HPP

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeColoredLog(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeBasicLog(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeErrorLog(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeWarnLog(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerLogRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif
