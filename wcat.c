#include<stdio.h>
#include<stdlib.h>

int main(int argc,char * argv[]){
    int i=1;
    
    while(i<argc){
    const char *filename=argv[i];
    FILE *file=fopen(filename,"r");
   

    if(!file){
        printf("wcat: cannot open file\n");
        exit(1);
    }
    else{
        char buffer[100];
        while(fgets(buffer,100,file)){
            printf("%s",buffer);
        }
        fclose(file);
    }
   
    i++;
}
exit(0);

    }



