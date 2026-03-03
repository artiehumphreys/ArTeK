#pragma once

#include <string>

enum TokenType {
  TOKEN_TEXT,
  TOKEN_COMMAND,
  TOKEN_SYMBOL,
  TOKEN_ALIGN,
  TOKEN_NEWLINE,
  TOKEN_BEGIN_ENV,
  TOKEN_END_ENV,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_MATH_INLINE,
  TOKEN_SUPERSCRIPT,
  TOKEN_SUBSCRIPT,
  TOKEN_COMMENT,
  TOKEN_EOF,
  TOKEN_ERROR,
};

struct Token {
  TokenType type;
  std::string value;
  int line;
  int column;
};
