#pragma once

// Still don't know why this definition is necessary, but it is required to
// inherit from yyFlexLexer.
// https://stackoverflow.com/questions/40663527/how-to-inherit-from-yyflexlexer
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include "token.hpp"
#include <iostream>
#include <string>

class Scanner : public yyFlexLexer {
public:
  // yyFlexLexer object requires input and output streams
  Scanner(std::istream *in = nullptr, std::ostream *out = nullptr)
      : yyFlexLexer(in, out), currentToken() {}

  int getNextToken();
  Token getCurrentToken() const;

  virtual int yylex();

private:
  void setToken(TokenType type, const std::string &value);

  Token currentToken;
  static int yycolumn;
};
