#include "scanner.hpp"
#include "token.hpp"
#include <fstream>
#include <iostream>
#include <string>

constexpr const char *tokenTypeToString(TokenType type) {
  switch (type) {
  case TOKEN_TEXT:
    return "Text";
  case TOKEN_COMMAND:
    return "Command";
  case TOKEN_SYMBOL:
    return "Symbol";
  case TOKEN_ALIGN:
    return "Align";
  case TOKEN_NEWLINE:
    return "Newline";
  case TOKEN_BEGIN_ENV:
    return "Begin env";
  case TOKEN_END_ENV:
    return "End env";
  case TOKEN_LBRACE:
    return "LBrace";
  case TOKEN_RBRACE:
    return "RBrace";
  case TOKEN_MATH_INLINE:
    return "Math Inline";
  case TOKEN_SUPERSCRIPT:
    return "Superscript";
  case TOKEN_SUBSCRIPT:
    return "Subscript";
  case TOKEN_COMMENT:
    return "Comment";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_ERROR:
    return "Error";
  }
  return "Unknown";
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: scanner <filename>" << '\n';
    return 1;
  }

  std::string filename = argv[1];
  std::ifstream inputFile(filename);

  if (!inputFile.is_open()) {
    std::cerr << "Error: could not open file '" << filename << "'" << '\n';
    return 1;
  }

  Scanner scanner(&inputFile);

  while (true) {
    int token_type = scanner.getNextToken();

    if (token_type == TOKEN_EOF) {
      break;
    }

    Token token = scanner.getCurrentToken();

    std::cout << tokenTypeToString(token.type) << ": " << token.value
              << " [" << token.line << ":" << token.column << "]" << '\n';
  }

  return 0;
}
