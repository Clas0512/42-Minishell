#include "minishell.h"

void    word_counter(s_lex *info)
{
    long    i;
    long    s_q;
    long    d_q;
    char    *str;

    d_q = 0;
    s_q = 0;
    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 39)
            s_q++;
        if (str[i] == 34)
            d_q++;
        if ((d_q % 2 == 0) && (s_q % 2 == 0) && str[i] != ' ' && (str[i + 1] == '\0' || str[i + 1] == ' '))
        {
            printf("%c %ld\n", str[i], i);
            info->word_count++;
        }
        i++;
    }
}