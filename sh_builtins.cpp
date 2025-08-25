#include <string>
#include <sys/wait.h>
#include <sys/types.h>
#include <sstream>
#include <cstring>
#include "sh_builtins.h"

char *builtin_str[SH_BUILTINS_SIZE] = {
    (char *) "cd",
    (char *) "cwd",
    (char *) "oldcwd",
    (char *) "help",
    (char *) "exit"
};

int (*builtin_func[SH_BUILTINS_SIZE]) (char **) = {
    &sh_cd,
    &sh_cwd,
    &sh_oldcwd,
    &sh_help,
    &sh_exit
};

std::string join_args(char **args, int start) {
    std::ostringstream oss;
    for (int i = start; args[i] != nullptr; i++) {
        if (i > start) oss << " ";
        oss << args[i];
    }
    return oss.str();
}

int sh_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "sh: expected argument to \"cd\"\n");
        return 1;
    } 

    std::string path = join_args(args, 1);
    if (chdir(path.c_str()) != 0){
        perror("sh");
    }
    strcpy(oldcwd, cwd);
    getcwd(cwd, sizeof(cwd));
    return 0;
}

int sh_help(char **args) {
    (void)args;
    printf("Adarsh Gorai's SH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (int i = 0; i < SH_BUILTINS_SIZE; i++) {
        printf(" %s\n", builtin_str[i]);
    }

    printf("Use man command for information on other programs\n");
    return 0;
}

int sh_exit(char **args) {
    (void)args;
    kill(-getpgrp(), SIGTERM);
    return 0;
}
int sh_cwd(){
    printf(cwd, "hello\n");
    return 0;
}
int sh_cwd(char **args){
    // char ** s = args;
    (void) args;
    printf(cwd);
    printf("\n");
    return 0;
}

int sh_oldcwd(char ** args){
    (void) args;
    printf(oldcwd);
    printf("\n");
    return 0;
}

void sh_set_cwd(){
    getcwd(cwd, sizeof(cwd));
    strcpy(oldcwd, cwd);
}