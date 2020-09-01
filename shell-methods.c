
#include <stddef.h>
#include "shell-methods.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

char * path; //Path for changeDirectory()


void redirectCommand(char ** token, int tokenSize, int point){
    char ** args;
    args = (char**)malloc(sizeof(char*) * tokenSize);
    for(int j = 0; j < point; j++){
        args[j] = token[j]; 
    }

    char * filename;
    filename = token[tokenSize - 1]; //Filename in the redirect
    pid_t p = fork();
    if(p == 0){
        int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
        execvp(*args, args); //Command executed
        if(p < 0){
                perror("execvp");
            }
        exit(1);
    }else{
        wait(NULL);
    }
}

//Function check for ' ^C '
//Checks if the signal is SIGINT
void signal_handler(int signal){
    if(signal  == SIGINT){
        printf("\n");
        exit(1);
    }
}

/* Parse Function which splits the input string into tokens.
   Tokens were created using strtok.
   The execute command is then called at the end of this function using
   the tokens that were made.
*/
void parse(char input_str[]){
    signal(SIGINT, signal_handler); //SIGINT checker
    char **token = malloc(sizeof(char*)); //Token pointer created
    int tokenSize = 0;
    char delimiters[]=" \t\n";
    char * str = NULL;
    str = strtok(input_str, delimiters);
    //Tokens are created. Delimiters are taken away.
    while(str != NULL){
        token[tokenSize] = str;
        tokenSize++;
        token = realloc(token, (tokenSize + 1) * sizeof(char*));
        str = strtok(NULL, delimiters);
    }
    
    token[tokenSize] = NULL; //Last token is set to NULL. 
                            // Shell command fails and succeeds randomnly if this is not set.
    executeCommand(token, tokenSize);
}




void changeDirectory(char ** token, int tokenSize){
    //Changes current working directory to home.
    if(tokenSize == 1){
        path = getenv("HOME");
        chdir(path);
    }
    else if(tokenSize == 2){ 
        chdir(token[1]);
    }
}

void executeCommand(char ** token, int tokenSize){
    //Checks each token to see if a redirect is needed.
   int flag = 0; //1 : redirect / 0 : Normal command
   int point = 0;
   char ** args;
   args = (char**)malloc(sizeof(char*) * tokenSize);
    for(int i = 0; i < tokenSize; i++){
        if(strcmp(token[i], ">") == 0){
            flag++;
            point = i;
    }
    }

    //Exits Shell
    if(strcmp(token[0], "exit") == 0){
        exit(0);
    }

    //Changes directiory if cd is used
    if(strcmp(token[0], "cd") == 0){ 
       changeDirectory(token, tokenSize);
       return;
       
    }

    //Redirect e.g : "echo test > file"
    if(flag == 1){  
        redirectCommand(token, tokenSize, point);
        return;
    }

    //Shell command executed through child process
    if(flag == 0){
        pid_t pid = fork(); //Regular command is executed
        if(pid == 0){
            int i = execvp(*token, token);
            if(i < 0){
                perror("execvp");
            }
            exit(1); 
            }else{
            wait(NULL);
        }
    }
}

/* Current month, day, and time obtained from time.h library */
void timeDate(){
    time_t t_time;
    struct tm* tm_info;
    char timeArr[50];
    time(&t_time);
    tm_info = localtime(&t_time);
    strftime(timeArr, 50, "%d/%m %H:%M", tm_info);
    printf("[%s]", timeArr);
}