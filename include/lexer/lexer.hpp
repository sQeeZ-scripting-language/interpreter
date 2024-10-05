#ifndef LEXER_HPP
#define LEXER_HPP

#include <cctype>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "lexer/token_recognizers/data_recognizers.hpp"
#include "lexer/tokens/token.hpp"

class Lexer {
public:
  Lexer(const std::string& code);
  std::vector<Token> tokenize(bool devMode);
  void lexSpecialCases(Token previousToken, DataRecognizer& dataRecognizer, std::unique_ptr<Token>& tokenPtr);
  void getNextToken(std::unique_ptr<Token>& tokenPtr);
  void extractCommentLiteral(std::unique_ptr<Token>& tokenPtr);
  void extractStringLiteral(std::unique_ptr<Token>& tokenPtr);
  std::string extractToken();
  bool checkKeyword(const std::string& keyword);
  void skip(size_t size);
  void skipWhitespace();
  char advance();
  char peek();
  bool isEOF();

  const std::string code;
  size_t pos;
  std::unordered_map<std::string, std::function<void(Lexer&, std::unique_ptr<Token>&)>> tokenRecognizers;

private:
  void registerTokenRecognizers();
  void log(Token token, bool devMode);
  std::vector<Token> tokens;
};

#endif
