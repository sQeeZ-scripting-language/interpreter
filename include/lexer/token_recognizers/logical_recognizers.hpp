#ifndef LOGICAL_RECOGNIZERS_HPP
#define LOGICAL_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeEqual(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeNotEqual(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeGreater(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeLess(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeGreaterEqual(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeLessEqual(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeAnd(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeOr(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeNot(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerLogicalRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif
