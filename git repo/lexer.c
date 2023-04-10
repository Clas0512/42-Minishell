#include "lexer.h"
#include <signal.h>
#include <stdlib.h>

void    init_struct(s_lex *info, char *str)
{
    info->last_quotes = 0;
    info->main_str = str;
    info->strlen = ft_strlen(str);
    quotes_counter(info);
    printf("single quotes count = %ld\n", info->s_q);
    printf("double quotes count = %ld\n", info->d_q);
}

char **lexer(char *str)
{
    s_lex *info;

    info = malloc(sizeof(s_lex) * 2);
    init_struct(info, str);
    word_counter(info);

    printf("bulunan kelime sayisi = %ld\n", info->word_count);
    return (NULL);
}

int main(int ac, char **av)
{
    char *str = av[1];
    //char str[] = "'asd''|''|''cde'";
    lexer(str);
    return (0);
}