#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_lex
{
    void    *main_str;
	int		*sgn_lst;
    long    d_q;
    long    s_q;
    char    last_quotes;
    long    strlen;
    long    word_count;
}			s_lex;

long    ft_strlen(char *str);
void    quotes_counter(s_lex *info);
void    word_counter(s_lex *info);

#endif
