#include "lexer.h"

long    quotes_counter(s_lex *info)
{
    long    i;
    long    q;
    char    *str;

    str = info->main_str;
    i = 0;
    q = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
            q++;
        i++;
    }
    return (q);
}

long    word_reduce(s_lex *info)
{
    char    *str;
    int     i;
    int     q;

    q = 0;
    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        if ((q % 2 == 0) && str[i] == 39)
            q++;
        if ((q % 2 == 1) && str[i] == 39 && str[i + 1] == 39 && str[i - 1] != 32)
        {
            printf("bura %d\n", i);
            if (info->word_count > 1)
                info->word_count--;
            q++;
        }
        i++;
    }
}