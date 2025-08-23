#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>

#define SH_RL_BUFFER 1024
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\n\r\a"
#define MAX_ARGS 64

char *sh_read_line(void){
    char *line = NULL;
    ssize_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  
        } else  {
            perror("sh: getline\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

void sh_run(char **args, int in_fd, int out_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        if (in_fd != 0) {
            dup2(in_fd, 0);
            close(in_fd);
        }
        if (out_fd != 1) {
            dup2(out_fd, 1);
            close(out_fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " \n");
    while (args[i] != NULL) {
        
        i++;
        args[i] = strtok(NULL, " \n");
    }
}
int sh_launch(char **commands) {
    int i = 0;
    int in_fd = 0;
    int fd[2];
    pid_t pid;
    char *args[MAX_ARGS];

    while (commands[i] != NULL) {
        parse_input(commands[i], args);
        if (commands[i+1] != NULL) {
            pipe(fd);
            sh_run(args, in_fd, fd[1]);
            close(fd[1]);
            if (in_fd != 0) close(in_fd);
            in_fd = fd[0];
        } else {
            sh_run(args, in_fd, 1); 
            if (in_fd != 0) close(in_fd);
        }
        i++;
    }
    
    while (wait(NULL) > 0);
    return 1;
}




int sh_execute(char **commands) {
    int i;

    if (commands[0] == NULL) {
        return 1;
    }

    // for (i = 0; i < sh_num_builtins(); i++) {
        
    // }

    return sh_launch(commands);
}

char **sh_split_line(char *line){
    int bufsize = SH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;
    
    if(!tokens) {
        fprintf(stderr, "sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, "|\n");
    while (token != NULL) {
        
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += SH_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if(!tokens) {
                free(tokens_backup);
                fprintf(stderr, "sh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, SH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

void sh_loop(void){
    char *line;
    char **commands;
    int status;

    do {
        printf("> ");
        line = sh_read_line();
        commands = sh_split_line(line);
        status = sh_execute(commands);

        free(line);
        free(commands);

    } while (status);
}

int main(){

    sh_loop();

}
