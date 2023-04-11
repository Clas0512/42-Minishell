#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct t_lex
{
    void    *main_str;
    long    d_quotes_count;
    long    s_quotes_count;
    long    strlen;
    long    word_count;
}       s_lex;

void    quotes_counter(s_lex *info);
void    word_counter(s_lex *info);

#endif
