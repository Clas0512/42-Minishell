#ifndef STRING_H
# define STRING_H

#include "minishell.h"

size_t	length(char *string);
size_t	array_length(char **strings);
char *duplicate(char *string);
char *join(char **strings);

#endif