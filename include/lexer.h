#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_manager
{
	int	length;
	int	current_wc;
	int	j;
	int	r;
}			t_manager;

typedef struct s_lex
{
	char		*main_str;
	char		*flags;
	long		d_q;
	long		s_q;
	char		last_quotes;
	int			strlen;
	int			word_count;
	char		starter_quotes;
	char		**main_line;
	char	    **line;
	int 	    a;
	int			b;
	bool		error;
	int			last_quotes_count;
	char		**error_str;
	t_manager	manager;
}			t_lex;

void	helper(t_lex *info, int r, char mod);
char    **lexer(char *str);
int		letter_counter_in_quotes(char *str, char pvt, int *i);
int		quotes_passer(char *str, int *i, char pvt);
int		quotes_counter_spcl(char *str, char pvt, int i);
int     is_rdrct(char *str, int i);
int     is_merge_quotes(char *str, int i, char pvt);
int		quotes_passer(char *str, int *i, char pvt);
int     is_rdrct(char *str, int i);
int     is_valid_dollar(t_lex *info, int i);
int     word_control_1(t_lex *info, int i);
int		is_word_final_quotes(char *str, int i);
int		is_word_final_basic(char *str, int i);
int		word_passer(char *str, int *i);
void    set_line(t_lex *info, char *str, char **line);
void    quotes_counter(t_lex *info, int i);
void    init_struct(t_lex *info, char *str);
void    word_manager(t_lex *info, char *str);
void    tokenize_q_str(t_lex *info, int wd, char flag);
int		is_invalid_str(char *str, int i, int limit);
void	invld_quotes_str(t_lex *info);
void	word_counter(t_lex *info);

#endif
