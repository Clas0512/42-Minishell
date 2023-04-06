#ifndef LEXER_H
# define LEXER_h

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_lex
{
    void    *main_str;
    long    quotes_count;
    long    strlen;
    long    word_count;
}       s_lex;

long    quotes_counter(s_lex *info);
long    ft_strlen(char *str);
void    word_counter(s_lex *info);
long    word_reduce(s_lex *info);

#endif