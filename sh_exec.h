#ifndef SH_EXEC_H
#define SH_EXEC_H

#include <sys/types.h>
#include "sh_builtins.h"
// #ifdef __cplusplus
// extern "C" {
// #endif
// char cwd[PATH_MAX];
int sh_cwd();
// char cwd[PATH_MAX];

int sh_cwd(char **args);
void sh_set_cwd();
// int sh_cwd(std::optional<char **>args = {});


pid_t sh_run(char **args, int in_fd, int out_fd);
int sh_launch(char **commands);
void parse_input(char *input, char **args);

// #ifdef __cplusplus
// }
// #endif

#endif // SH_EXEC_H
