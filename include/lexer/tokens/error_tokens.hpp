#ifndef ERROR_TOKEN_HPP
#define ERROR_TOKEN_HPP

enum class ErrorToken {
  IDENTIFIER_NOT_FOUND,
  IDENTIFIER_RESERVED_KEYWORD,
  IDENTIFIER_ALREADY_EXISTS,
  IDENTIFIER_INVALID_FORMAT,
  IDENTIFIER_INVALID_TYPE
};

#endif