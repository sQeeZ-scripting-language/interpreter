#ifndef OPERATOR_RECOGNIZERS_HPP
#define OPERATOR_RECOGNIZERS_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "lexer/lexer.hpp"

using TokenRecognizer = std::function<void(Lexer&, std::unique_ptr<Token>&)>;

void recognizeAssign(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeAddition(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSubtraction(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeMultiplication(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDivision(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeModulus(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeAdditionAssignment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeSubtractionAssignment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeMultiplicationAssignment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDivisionAssignment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeModulusAssignment(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeIncrement(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizeDecrement(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);
void recognizePotentiation(Lexer& lexer, std::unique_ptr<Token>& tokenPtr);

void registerOperatorRecognizers(std::unordered_map<std::string, TokenRecognizer>& tokenRecognizers);

#endif
