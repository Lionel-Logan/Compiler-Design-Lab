#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char eclosure[10][10][10];
int size[100];
char closure[10][10];

void findeclosure(char state[],int*count){
   char from[10],arrow[10],to[10];
   FILE *f =fopen("input.txt","r");
   while(fscanf(f,"%s %s %s",from,arrow,to)==3){
        if (strcmp(state,from)==0 && strcmp(arrow,"e")==0){
            int already=0;
            for(int i=0;i<*count;i++){
                if(strcmp(closure[i],to)==0){
                    already=1;
                    break;
                }
            }
            if(already==0){
                strcpy(closure[*count],to);
                *count=*count+1;
                findeclosure(to,count);
            }
        }
   }
   fclose(f);

}

void convert(char state[],int index, char symbol[]){
    char nfa[10][10];
    int c=0;
    int n=size[index];

    for(int i=0;i<n;i++){
        char *p=eclosure[index][i];
        char from[10],arrow[10],to[10];
        FILE *f=fopen("input.txt","r");
        while(fscanf(f,"%s %s %s",from,arrow,to)==3){
            if(strcmp(from,p)==0 && strcmp(arrow,symbol)==0){
                int temp_count=0;
                strcpy(closure[temp_count],to);
                temp_count++;
                findeclosure(to,&temp_count);

                for(int k=0;k<temp_count;k++){
                    char *new=closure[k];
                    int already=0;
                    for(int i=0;i<c;i++){
                        if(strcmp(nfa[i],new)==0){
                            already=1;
                            break;
                        }
                    }

                    if(already==0){
                        strcpy(nfa[c++],new);
                    }
                }

            }

        }
        fclose(f);
    }
    printf("  delta_new(%s, %s) = { ", state, symbol);
    if (c == 0) {
        printf("NULL }\n");
        return;
    }
    
    for (int i = 0; i < c; i++) {
         printf("%s ", nfa[i]);
    }
    printf("}\n");
}
void main(){
    int e=0;
    int n;
    printf("enter the number of states:");
    scanf("%d",&n);
    char state[n][10];
    for(int i=0;i<n;i++){
        printf("->");
        scanf("%s",state[i]);
    }
    for(int j=0;j<n;j++){
        int count=0;
        strcpy(closure[count],state[j]);
        count=count+1;
        findeclosure(state[j],&count);
        for(int k=0;k<count;k++){
            strcpy(eclosure[j][k],closure[k]);
        }
        size[j]=count;
        printf("epsilon closure of %s\n",state[j]);
        for (int k=0;k<count;k++){
            printf("%s",closure[k]);
        }
        printf("\n");
    }
    char inputsymbol[n][20];
    int symbol=0;
    char tempfrom[10],temparrow[10],tempto[10];
    FILE*f=fopen("input.txt","r");
    while(fscanf(f,"%s %s %s",tempfrom,temparrow,tempto)==3){
        if (strcmp(temparrow,"e")!=0){
            int already=0;
            for(int i=0;i<symbol;i++){
                if (strcmp(inputsymbol[i],temparrow)==0){
                    already=1;
                    break;
                }
            }
            if (already==0){
                strcpy(inputsymbol[symbol],temparrow);
                symbol++;

            }
        }
    }
    fclose(f);
    for(int i=0; i < symbol; i++) {
        printf("%s ", inputsymbol[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<symbol;j++){
            convert(state[i],i,inputsymbol[j]);
        }
    }

}