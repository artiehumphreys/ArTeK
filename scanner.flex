%{
    #include <token.h>
    #include <string>
    extern int yylineno;
    int yycolumn = 1;

    Token createToken(TokenType type, std::string value) {
        Token token;
        token.type = type;
        token.value = value;
        token.line = yylineno;
        token.column = yycolumn;
        yycolumn += yyleng;
        return token;
    }

%}

%option noyywrap
%option c++

LETTER          [A-Za-z]
DIGIT           [0-9]
COMMAND_NAME    {LETTER}+
ENV_NAME        {LETTER}+
TEXT            [^\\{}\n&%$]+ #include math characters (+, -, =, etc.) for simplicity

%%

(" "|\t)            ; # skipping whitespace
