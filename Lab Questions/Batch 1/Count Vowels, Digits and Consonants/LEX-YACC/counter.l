%{
    #include "y.tab.h"    
%}

%%

.*      {return INPUT;}

%%

int yywrap(){
    return 1;
}