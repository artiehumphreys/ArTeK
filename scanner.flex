%{
#include <token.h>
#include <string>
%}

LETTER          [a-zA-Z]
DIGIT           [0-9]
TEXT            {LETTER}+
COMMAND         \\{TEXT}

%%
