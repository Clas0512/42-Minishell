#include "lexer.h"

long    ft_strlen(char *str)
{
    long    i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void    word_counter(s_lex *info)
{
    long    i;
    long    q;
    char    *str;

    q = 0;
    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
            q++;
        if ((q % 2 == 0) && str[i] != ' ' && (str[i + 1] == '\0' || str[i + 1] == ' '))
        {
            printf("%c %ld\n", str[i], i);
            info->word_count++;
        }
        i++;
    }
//    if (info->quotes_count > 2)
//        word_reduce(info);
}