#include "lexer.h"

void    quotes_counter(s_lex *info)
{
    long    i;
    long    d_q;
    long    s_q;
    char    *str;

    str = info->main_str;
    i = 0;
    info->s_q = 0;
    info->d_q = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
            info->s_q++;
        if (str[i] == 34)
            info->d_q++;
        i++;
    }
}
