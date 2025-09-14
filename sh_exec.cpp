#include "sh_exec.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
// #include "sh_builtins.h"

#define MAX_ARGS 64
// int sh_cd(**args);
void parse_input(char *line, char **args) {
    int i = 0;
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

pid_t sh_run(char **args, int in_fd, int out_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        

        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        for (int i = 0; args[i]; i++) {
            if (strcmp(args[i], "<") == 0) {
                if (args[i+1] == NULL) {
                    fprintf(stderr, "syntax error: no file after <\n");
                    exit(EXIT_FAILURE);
                }
                int fd = open(args[i+1], O_RDONLY);
                if (fd < 0) {
                    perror("open for input");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[i] = NULL;
                break;
            }
            if (strcmp(args[i], ">") == 0) {
                if (args[i+1] == NULL) {
                    fprintf(stderr, "syntax error: no file after >\n");
                    exit(EXIT_FAILURE);
                }
                int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open for output");
                    exit(EXIT_FAILURE);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
                break;
            }
            
        }
        for (int i = 0; i < SH_BUILTINS_SIZE; i++){
            if (strcmp(args[0], builtin_str[i]) == 0){
                return builtin_func[i](args);
                // return 0;
            }
        }
        // printf(args[0]);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    return pid;
}

int sh_launch(char **commands) {
    int i = 0;
    int in_fd = 0;
    int fd[2];
    pid_t child_pid;
    int status = 0;
    char *args[MAX_ARGS];

    while (commands[i] != NULL) {
        // printf(commands[i]);
        // printf("\n");
        if (commands[i+1] && strcmp(commands[i+1], "&") == 0){
            in_fd = 0;
            parse_input(commands[i], args);
            printf("here");
            child_pid = sh_run(args, in_fd, 1);
            
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                break;
            }
            i++;
            // i++;

        }
        parse_input(commands[i], args);
        if (commands[i+1] != NULL) {
            pipe(fd);
            child_pid = sh_run(args, in_fd, fd[1]);
            close(fd[1]);
            if (in_fd != 0) close(in_fd);
            in_fd = fd[0];
        } else {
            child_pid = sh_run(args, in_fd, 1);
            if (in_fd != 0) close(in_fd);
        }
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            break;
        }
        i++;
    }
    while (wait(NULL) > 0);
    return 1;
}