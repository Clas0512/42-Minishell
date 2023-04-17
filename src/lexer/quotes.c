#include "minishell.h"

void    quotes_counter(s_lex *info)
{
    long    i;
    long    d_q;
    long    s_q;
    char    *str;

    str = info->main_str;
    i = 0;
    s_q = 0;
    d_q = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
            s_q++;
        if (str[i] == 34)
            d_q++;
        i++;
    }
    info->d_quotes_count = d_q;
    info->s_quotes_count = s_q;
}
