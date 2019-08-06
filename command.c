#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define STR_SIZE 256
#define COM_SIZE 10
#define DEBUG 0

int main()
{
    pid_t pid;
    int status = 0, cycle = 1, i = 0, len = 0;
    char input[STR_SIZE];
    char *ptr_lex;
    char *arg[COM_SIZE];
    while(cycle)
    {
        memset(&input[0], 0, sizeof(input));
        memset(&arg[0], 0, sizeof(arg));
        
        printf("COMMAND: \n");
        if(!fgets(input, STR_SIZE, stdin))
        {
            perror("Input error");
            exit(-1);
        }
        if(!strcmp(input, "exit\n"))
        {
            cycle = 0;
            printf("EXIT\n");
            break;
        }
        ptr_lex = strtok(input, " ");
        i = 0;
        while(ptr_lex)
        {
            arg[i] = ptr_lex;
            ptr_lex = strtok(NULL, " ");
            i++;
        }
        len = strlen(arg[i - 1]);
        arg[i - 1][len - 1] = '\0';         //remove \n
        ptr_lex = arg[0];
        pid = fork();
        if(!pid)
        {
            execvp(ptr_lex, arg);
            perror("Command error");
            exit(-2);
        }else{
            wait(&status);
#if DEBUG
            printf("%d\n", status);
#endif
        }
    }
    exit(0);
}
