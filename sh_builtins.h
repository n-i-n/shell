#ifndef SH_BUILTINS_H
#define SH_BUILTINS_H
#define SH_BUILTINS_SIZE 5
#define PATH_MAX 1024

#include <sys/types.h>

extern char cwd[PATH_MAX];
extern char oldcwd[PATH_MAX];
extern char *builtin_str[SH_BUILTINS_SIZE];
extern int (*builtin_func[SH_BUILTINS_SIZE])(char **);

int sh_cd(char **args);
int sh_help(char **args);
int sh_exit(char **args);
int sh_cwd(char **args);
int sh_oldcwd(char **args);
int sh_cwd();
void sh_set_cwd();

#endif 