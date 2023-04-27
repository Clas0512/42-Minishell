/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 03:56:41 by aerbosna          #+#    #+#             */
/*   Updated: 2023/04/28 02:28:42 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "redirection.h"
# include "collector.h"
# include "lexer.h"
# include "pipe.h"
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

typedef struct s_shell
{
	char		**environments;
	char		*cwdr;
	int			pipe_count;
	int			pipearg_count;
	char		**pipeargs;
	char		*echo_n_control;
	int			echo_n;
	int			exit_status;
	t_collector	collector;
	t_pipe		pipe;
	t_redir		redir;
	t_redir2	redir2;
	t_redir3	redir3;
}	t_shell;

extern t_shell	g_shell;

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
int		echo_mid_checker(char *arg);

//promptline
void	read_the_line(char *line, char **linefornow);

//executor
char	*get_full_path(char *path, char *c, char *exec_name);
int		execute(char *exec_name, char **args);
char	*return_exec_path(char *exec_name);
char	*get_env_variable(char *var_name);
int		if_execexist(char *exec_name);

//pipe
int		pipe_exists(char *input);
void	pipe_execute(char **pipeargss);
void	pipe_execute_init(int mod);
void	parent_proc();
void	child_proc();

//redirections
int		redirection_exists(char *line);
void	redirection_redirector(char **linefornow);
void	infile(char **args);
void	outfile(char **args);
void	append(char **args);
void	heredoc(char **command, char *delimiter);
void	redir_init(void);
void	append_init(void);

//sytnax
int	check_syntax_builtin(char **linefornow);
int check_syntax_builtin2(char **linefornow);
int check_syntax_builtin3(char **linefornow);
int	check_syntax_redir(char **linefornow);
int	check_exit_status(char **linefornow);

#endif