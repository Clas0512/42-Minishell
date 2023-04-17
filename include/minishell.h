#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include "redirection.h"
#include "collector.h"
#include "command.h"
#include "string.h"
#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

typedef struct s_lexer
{
	bool 	d_quote;
	bool 	s_quote;
	size_t	string_len;
}	t_lexer;

typedef struct s_shell
{
	char **environments;
	t_commander commander;
	t_collector collector;
}	t_shell;

extern t_shell shell;

//lexer
bool update_status(bool *double_quote, bool *single_quote, char c);
void skip_quotes(char *input, size_t *string_len, char quote, size_t *index);
void lexer_size(char *input, int *i);
void lexer_template(t_lexer *lex, char *input, void (*f)(t_lexer, int *));

//signals
void	handle_signal(int sig);

//built-in's
void	echo(int ac, char **av);
void 	pwd();
void	export(char **newenvname);
void	unset_env(char *unsettling);
void	init_env();
void	print_env();
void	exit_minishell(char **exitargs);

char	*get_pwd(void);
void	set_env(char *env);
 void	changenewpwd();
void	change_dir(char **cdargs);
char	*get_env(char *env); 

#endif