#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        while (1) {
            printf("wish> ");
            char *lineptr = NULL;
            size_t len = 0;
            ssize_t read;

            read = getline(&lineptr, &len, stdin);

            if (strcmp(lineptr, "exit\n") == 0) {  // must check with \n because getline includes it
                exit(0);
            }

            if (read == -1) {
                exit(0);
            }

            lineptr[read - 1] = '\0';  // remove the newline character
            if(lineptr[0]!='.'){

            char *path = "/bin/";
            char *rempath = malloc(100);  // buffer to store /bin/ + cmd
            rempath[0] = '\0';

            char *finalpath = strcat(rempath, path);
            char *cmd = strsep(&lineptr, " ");
            finalpath = strcat(rempath, cmd);  // append cmd to /bin/

            int acces = access(finalpath, X_OK);

            if (acces == 0) {
                int rc = fork();
                if (rc == 0) {
                    char *arg[100];
                    arg[0] = cmd;
                    int ptr = 1;
                    while (lineptr) {
                        arg[ptr] = strsep(&lineptr, " ");
                        ptr++;
                    }
                    arg[ptr] = NULL;
                    execv(finalpath, arg);
                } else {
                    int wc = wait(NULL);
                }
            } else {
                printf("wrong path\n");
            }
            }
            else{
                int rc=fork();
                if(rc==0){
                    close(STDOUT_FILENO);
                    open("path.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
                    char*agg[2];
                    agg[0]="pwd";
                    agg[1]=NULL;
                    execv("/bin/pwd",agg);

                }
                else{
                    wait(NULL);
                    char *lineptrr = NULL;
            size_t lenn = 0;
            ssize_t readd;
            FILE *fp=fopen("path.txt","r");
            readd = getline(&lineptrr, &lenn, fp);
            lineptrr[readd-1]='\0';
            strsep(&lineptr,"/");
           
            
char *rempath = malloc(100);  // buffer to store /bin/ + cmd
            rempath[0] = '\0';
           strcat(rempath,lineptrr);
        strcat(rempath,"/");
           // printf("%s\n",rempath);
            char*cmd=strsep(&lineptr," ");
            strcat(rempath,cmd);
            // printf("%s\n",rempath);

            // printf("%s\n",cmd);
            char*argvv[2];
            argvv[0]=cmd;
            argvv[1]=NULL;
            execv(rempath,argvv);
                }
            }

            // Memory leak: rempath and lineptr not freed
            // free(rempath);  ← should be added
            // free(lineptr);  ← should be added
        }
    }
}
