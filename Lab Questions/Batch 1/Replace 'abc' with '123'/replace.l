%{
    #include <stdio.h>    
    #include <string.h>
%}

%%

.*abc.*     {char* content = strdup(yytext);
for(int i = 0; i <= strlen(content) - 3; i++){
    if(content[i] == 'a' && content[i+1] == 'b' && content[i+2] == 'c'){
        content[i] = '1';
        content[i+1] = '2';
        content[i+2] = '3';
        i += 3;
    }
}
printf("%s\n", content);
}

.*          {printf("%s\n", yytext);}

%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}