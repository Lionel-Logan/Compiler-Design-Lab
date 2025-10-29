#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int n;
char production[20][10];
void addtoset(char *result,char c){
    for(int i=0;result[i]!='\0';i++){
        if(result[i]==c){
            return;
        }
    }
    int len=strlen(result);
    result[len]=c;
    result[len+1]='\0';
}

void findfirst(char *result,char c){
    if((isupper(c))==0){
        addtoset(result,c);
        return;
    }

    for(int i=0;i<n;i++){
        if(production[i][0]==c){
            if(production[i][2]=='#'){
                addtoset(result,'#');
            }
            else{
                int j=2;
                while(production[i][j]!='\0'){
                    if(isupper(production[i][j])==0){
                        addtoset(result,production[i][j]);
                        break;
                    }
                    else{
                        char temp[10]="";
                        findfirst(temp,production[i][j]);
                        int flag=0;
                        for(int k=0;temp[k]!='\0';k++){
                            if(temp[k]!='#'){
                                addtoset(result,temp[k]);
                            }
                            else{
                                flag=1;
                            }
                        }
                        if(flag==0){
                            break;
                        }
                        j=j+1;
                        if (production[i][j]=='\0'){
                            addtoset(result,'#');
                        }
                    }
                }
            }
        }
    }

}
void findfollow(char*result,char c){
    if(production[0][0]==c){
        addtoset(result,'$');
    }
    for(int i=0;i<n;i++){
        for(int j=2;production[i][j]!='\0';j++){
            if(production[i][j]==c){
                if(production[i][j+1]!='\0'){
                    if(isupper(production[i][j+1])==0){
                        addtoset(result,production[i][j+1]);
                    }
                    else{
                        int flag=0;
                        char temp[10]="";
                        findfirst(temp,production[i][j+1]);
                        for(int k=0;temp[k]!='\0';k++){
                            if(temp[k]!='#'){
                                addtoset(result,temp[k]);
                            }
                            else{
                                flag=1;
                            }
                        }
                        if(flag==1){
                            char temp[10]="";
                            findfollow(temp,production[i][0]);
                            for (int k = 0; temp[k] != '\0'; k++)
                                addtoset(result, temp[k]);

                        }
                    }
                }
                else if (production[i][0]!=c){
                    char temp[10]="";
                    findfollow(temp,production[i][0]);
                    for(int o=0;temp[o]!='\0';o++){
                        addtoset(result,temp[o]);
                    }
                }
            }
        }
    }
}

void main(){
    printf("enter the nuber of productions");
    scanf("%d",&n);
    getchar();
    char first[10],follow[10];
    printf("enter the productions\n");
    for(int i=0;i<n;i++){
        fgets(production[i],10,stdin);
        for(int j=0;j<10;j++){
            if(production[i][j]=='\n'){
                production[i][j]='\0';
                break;
            }
        }
    }

    for(int i=0;i<n;i++){
        char c=production[i][0];
        memset(first,0,sizeof(first));
        findfirst(first,c);
        findfollow(follow,c);
        printf("first of %c == %s\n",c,first);
        printf("follow of %c == %s\n",c,follow);
    }

}