#ifndef ARRAY_RECOGNIZERS_HPP
#define ARRAY_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeLength(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizePush(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizePop(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeShift(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeUnshift(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSplice(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSlice(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeConcat(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeJoin(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeReverse(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSort(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeMap(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeFilter(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeReduce(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeIncludes(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeForEach(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeIndexOf(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerArrayRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif