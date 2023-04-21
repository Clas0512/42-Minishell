#ifndef LEXER_H
# define LEXER_H

typedef struct t_lex
{
    void	*main_str;
    long	d_q;
    long	s_q;
    char	last_quotes;
    int		strlen;
    int		word_count;
    char	starter_quotes;
    char	**main_line;
}			s_lex;

int     is_rdrct(char *str, int i);
int     is_merge_quotes(char *str, int i, char pvt);
void    set_line(s_lex *info, char *str, char **line);
void    quotes_counter(s_lex *info, int i);
void    word_counter(s_lex *info);
void    init_struct(s_lex *info, char *str);
char    **lexer(char *str);
int     is_rdrct(char *str, int i);
int     is_valid_dollar(s_lex *info, int i);
int     word_control_1(s_lex *info, int i);
void    word_counter1(s_lex *info, char *str);
int    quotes_passer(char *str, int *i, char pvt);

#endif
