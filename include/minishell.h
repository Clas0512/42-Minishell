/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 03:56:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/24 15:05:54 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "redirection.h"
# include "collector.h"
# include "command.h"
# include "string.h"
# include "lexer.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <limits.h>

typedef struct s_lexer
{
	bool	d_quote;
	bool	s_quote;
	size_t	string_len;
}	t_lexer;

typedef struct s_shell
{
	char		**environments;
	char		*cwdr;
	int			pipe_count;
	int			pipearg_count;
	char		**pipeargs;
	t_commander	commander;
	t_collector	collector;
}	t_shell;

extern t_shell	g_shell;

//lexer
bool	update_status(bool *double_quote, bool *single_quote, char c);
void	skip_quotes(char *input, size_t *string_len, char quote, size_t *index);
void	lexer_size(char *input, int *i);
void	lexer_template(t_lexer *lex, char *input, void (*f)(t_lexer, int *));

//signals
void	signal_handler(int sig);
void	init_signal(void);

//built-in's
void	echo(int ac, char **av);
void	pwd(void);
void	change_new_pwd(void);
void	unset_env(char **unsettling);
void	init_env(void);
void	print_env(void);
void	exit_minishell(char **exitargs);
void	export_env(char **newenvname);
char	*get_pwd(void);
void	set_env(char *env, char *str);
void	change_directory(char **cdargs);
char	*get_env(char *env);

//promptline
void	read_the_line(char *line, char **linefornow, int ac);

//executor
char	*get_full_path(char *path, char *c, char *exec_name);
int		execute(char *exec_name, char **args);
char	*return_exec_path(char *exec_name);
char	*get_env_variable(char *var_name);
int		if_execexist(char *exec_name);


//pipe
void	init_pipe(char *exec_name, char **pipe_args);
int		plumber(char **pipe_arg1,char **pipe_arg2);
int		pipe_exists(char *input);

#endif