#ifndef LEXER_H
# define LEXER_H

typedef struct s_line
{
    char **line;
    int a;
    int b;
}           t_line;

typedef struct s_lex
{
    void	*main_str;
    long	d_q;
    long	s_q;
    char	last_quotes;
    int		strlen;
    int		word_count;
    char	starter_quotes;
    char	**main_line;
    t_line    *ln;
}			t_lex;


int     is_rdrct(char *str, int i);
int     is_merge_quotes(char *str, int i, char pvt);
void    set_line(t_lex *info, char *str, char **line);
void    quotes_counter(t_lex *info, int i);
void    word_counter(t_lex *info);
void    init_struct(t_lex *info, char *str);
char    **lexer(char *str);
int     is_rdrct(char *str, int i);
int     is_valid_dollar(t_lex *info, int i);
int     word_control_1(t_lex *info, int i);
void    word_counter1(t_lex *info, char *str);
int    quotes_passer(char *str, int *i, char pvt);

#endif
