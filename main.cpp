#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sh_exec.h"
// #include "sh_exec.cpp"

#define SH_RL_BUFFER 1024
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\n\r\a"
#define MAX_ARGS 64

char cwd[PATH_MAX] = "";
char oldcwd[PATH_MAX] = "";


int sh_execute(char **commands) {

    if (commands[0] == NULL) {
        return 1;
    }

    return sh_launch(commands);
}

char **sh_split_line(char *line){
    int bufsize = SH_TOK_BUFSIZE, position = 0;
    char **tokens = (char **)malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;
    
    if(!tokens) {
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, "|&&\n");
    while (token != nullptr) {
        
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += SH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char*));

            if(!tokens) {
                free(tokens_backup);
                fprintf(stderr, "sh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(nullptr, SH_TOK_DELIM);
    }
    tokens[position] = nullptr;
    return tokens;
}

void custom_input(char* args, char **input){
    std::string msg = std::string(args) + ">";
    if ((input[0] = readline(msg.c_str())) != nullptr) {
        if (*input[0]) add_history(input[0]);
    }
}

void sh_loop(void){
    char *line;
    char **commands;
    int status;
    sh_set_cwd();

    do {
        custom_input(cwd, &line);
        commands = sh_split_line(line);
        status = sh_execute(commands);

        free(line);
        free(commands);

    } while (status);
}

int main(){
    sh_loop();
}