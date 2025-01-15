#ifndef TOKENTYPES_H
#define TOKENTYPES_H

#include <string>

enum class TokenType{
    TEXT,
    COMMAND,
    SYMBOL,
    ALIGN,
    NEWLINE,
    BEGIN_ENV,
    END_ENV,
    LBRACE,
    RBRACE,
    MATH_INLINE,
    SUPERSCRIPT,
    SUBSCRIPT,
    COMMENT,
    EOF_TOKEN,
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

#endif
