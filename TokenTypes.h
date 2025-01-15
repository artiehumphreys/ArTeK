#ifndef TOKENTYPES_H
#define TOKENTYPES_H

#include <string>

enum class TokenType{
    TEXT,
    COMMAND,
    SYMBOL,
    MATH_INLINE,
    MATH_DISPLAY,
    NEWLINE,
    EOF_TOKEN,
    BEGIN_ENV,
    END_ENV
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

#endif
