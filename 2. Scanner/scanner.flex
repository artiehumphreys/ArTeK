%{
    #include "scanner.h"
    #include <string>
    #include <iostream>
    #include "token.h"

    int Scanner::yycolumn = 1;
%}

%option c++
%option noyywrap
%option yyclass="Scanner"

LETTER          [A-Za-z]
DIGIT           [0-9]
COMMAND_NAME    {LETTER}+
ENV_NAME        {LETTER}+
TEXT            [^\\{}\n&%$]+
WHITESPACE      [ \t]+

%%

\\\{                        { this->setToken(TOKEN_TEXT, "{"); return TOKEN_TEXT; }
\\\}                        { this->setToken(TOKEN_TEXT, "}"); return TOKEN_TEXT; }

{WHITESPACE}                { yycolumn += yyleng; }

\n                          {
                                this->setToken(TOKEN_NEWLINE, "\n");
                                yycolumn = 1;
                                yylineno += 1;
                                return TOKEN_NEWLINE;
                            }

\\n                         {
                                this->setToken(TOKEN_NEWLINE, std::string(yytext));
                                yycolumn = 1;
                                yylineno += 1;
                                return TOKEN_NEWLINE;
                            }

\\{COMMAND_NAME}            { this->setToken(TOKEN_COMMAND, std::string(yytext)); return TOKEN_COMMAND; }

\\begin\{{ENV_NAME}\}       {
                                std::string env = std::string(yytext + 7, yyleng - 8);
                                this->setToken(TOKEN_BEGIN_ENV, env);
                                return TOKEN_BEGIN_ENV;
                            }

\\end\{{ENV_NAME}\}         {
                                std::string env = std::string(yytext + 5, yyleng - 6);
                                this->setToken(TOKEN_END_ENV, env);
                                return TOKEN_END_ENV;
                            }

\${TEXT}\$                  { this->setToken(TOKEN_MATH_INLINE, std::string(yytext + 1, yyleng - 2)); return TOKEN_MATH_INLINE; }

\_                          { this->setToken(TOKEN_SUBSCRIPT, "_"); return TOKEN_SUBSCRIPT; }

\^                          { this->setToken(TOKEN_SUPERSCRIPT, "^"); return TOKEN_SUPERSCRIPT; }

\{                          { this->setToken(TOKEN_LBRACE, "{"); return TOKEN_LBRACE; }

\}                          { this->setToken(TOKEN_RBRACE, "}"); return TOKEN_RBRACE; }

{TEXT}                      { this->setToken(TOKEN_TEXT, std::string(yytext)); return TOKEN_TEXT; }

&                           { this->setToken(TOKEN_ALIGN, "&"); return TOKEN_ALIGN; }

.                           { this->setToken(TOKEN_ERROR, std::string(yytext)); return TOKEN_ERROR; }

%[^\n]*                     { yycolumn += yyleng; }

<<EOF>>                     { this->setToken(TOKEN_EOF, ""); return TOKEN_EOF; }

%%

int Scanner::getNextToken() {
    return yylex();
}

void Scanner::setToken(TokenType type, const std::string& value) {
    currentToken.type  = type;
    currentToken.value = value;
    currentToken.line  = yylineno;
    currentToken.column = yycolumn;
    yycolumn += yyleng;
}

Token Scanner::getCurrentToken() const {
    return currentToken;
}

int yywrap() { return 1; }
