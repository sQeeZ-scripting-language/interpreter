#ifndef DATA_RECOGNIZERS_HPP
#define DATA_RECOGNIZERS_HPP

#include <cctype>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "lexer/tokens/token.hpp"

class DataRecognizer {
public:
  void storeIdentifier(std::string identifier, char type, std::unique_ptr<Token>& tokenPtr);
  void recognizeIdentifier(std::string identifier, std::unique_ptr<Token>& tokenPtr);
  void recognizeNumericLiteral(std::string number, std::unique_ptr<Token>& tokenPtr);

  std::unordered_map<std::string, char> identifiers;

private:
  bool isValidIdentifier(std::string identifier);
  bool isReservedKeyword(std::string identifier);
  char getType(std::string identifier);
};

#endif
