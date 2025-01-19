#include <iostream>
#include <fstream>
#include "token.h"
#include "scanner.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "Please include a file to scan." << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    Scanner scanner(&inputFile);

    while (true){
        int token_type = scanner.getNextToken();

        if (token_type == TOKEN_EOF) {
            break;
        }

        Token currentToken = scanner.getCurrentToken();

        switch (currentToken.type) {
            case TOKEN_ALIGN:
                cout << "Align" << endl;
                break;
            case TOKEN_BEGIN_ENV:
                cout << "Begin env " << currentToken.value << endl;
                break;
            case TOKEN_NEWLINE:
                cout << "Newline" << endl;
                break;
            case TOKEN_COMMAND:
                cout << "Command: " << currentToken.value << endl;
                break;
            case TOKEN_COMMENT:
                cout << "Comment: " << currentToken.value << endl;
                break;
            case TOKEN_END_ENV:
                cout << "End env " << currentToken.value << endl;
                break;
            case TOKEN_ERROR:
                cout << "Error on line " << currentToken.line << " Column " << currentToken.column << endl;
                break;
            case TOKEN_TEXT:
                cout << "Text: " << currentToken.value << endl;
                break;
            default:
                cout << "Other: " << currentToken.value << endl;
        }
    }

    inputFile.close();
    return 0;
}
