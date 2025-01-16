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
WHITESPACE      [ \t]+

%%

\\\{                        { return createToken(TOKEN_TEXT, "{"); }
\\\}                        { return createToken(TOKEN_TEXT, "}"); }

{WHITESPACE}                { yycolumn += yyleng; }

\\{COMMAND_NAME}            { return createToken(TOKEN_COMMAND, std::string(yytext)); }

\\begin\{{ENV_NAME}\}       {
                                std::string env = std::string(yytext + 7, yyleng - 8);
                                return createToken(TOKEN_BEGIN_ENV, env);
                            }

\\end\{{ENV_NAME}\}         {
                                std::string env = std::string(yytext + 5, yyleng - 6);
                                return createToken(TOKEN_END_ENV, env);
                            }

\$                          { return createToken(TOKEN_MATH_INLINE, "$"); }

\_                          { return createToken(TOKEN_SUBSCRIPT, "_"); }

\^                          { return createToken(TOKEN_SUPERSCRIPT, "^"); }

\{                          { return createToken(TOKEN_LBRACE, "{"); }

\}                          { return createToken(TOKEN_RBRACE, "}"); }

{TEXT}                      { return createToken(TOKEN_TEXT, std::string(yytext)); }

&                           { return createToken(TOKEN_ALIGN, "&"); }

%%

int yywrap() { return 1; }
