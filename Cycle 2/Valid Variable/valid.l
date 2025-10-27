%{
    #include "y.tab.h"
%}

%%

[0-9][a-zA-Z0-9_]*        {return INVALID;}
[a-zA-Z_][a-zA-Z0-9_]*    {return VALID;}

%%

int yywrap(){
    return 1;
}