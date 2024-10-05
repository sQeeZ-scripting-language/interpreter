#ifndef OBJECT_RECOGNIZERS_HPP
#define OBJECT_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeEntries(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeKeys(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeValues(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeHasOwnProperty(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDelete(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeTypeOf(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerObjectRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif