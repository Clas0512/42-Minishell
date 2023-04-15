#include "minishell.h"

void pwd() 
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } 
	else 
	{
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}
