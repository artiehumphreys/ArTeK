#ifndef SCANNER_H
#define SCANNER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include "token.h"
#include <string>
#include <iostream>

class Scanner : public yyFlexLexer {
public:
    Scanner(std::istream* in = nullptr, std::ostream* out = nullptr)
        : yyFlexLexer(in, out), currentToken() {}

    int getNextToken();
    Token getCurrentToken() const;

    virtual int yylex();
private:
    void setToken(TokenType type, const std::string& value);

    Token currentToken;
    static int yycolumn;
};

#endif
