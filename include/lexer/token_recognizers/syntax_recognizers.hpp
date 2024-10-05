#ifndef SYNTAX_RECOGNIZERS_HPP
#define SYNTAX_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeSemicolon(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeComma(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDot(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeColon(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSingleQuote(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDoubleQuote(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeOpenParenthesis(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeCloseParenthesis(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeOpenBracket(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeCloseBracket(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeOpenBrace(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeCloseBrace(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeInlineComment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizePipe(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizePipeOperator(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeArrow(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeHashtag(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeAt(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerSyntaxRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif
