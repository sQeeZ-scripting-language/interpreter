#ifndef KEYWORD_RECOGNIZERS_HPP
#define KEYWORD_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeVariable(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeConstant(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeIf(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeElse(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeElseIf(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeFor(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeWhile(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDo(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeFunction(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeReturn(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeIn(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeOf(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerKeywordRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif
