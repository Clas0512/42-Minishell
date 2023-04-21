#include "minishell.h"

void    quotes_counter(t_lex *info, int i)
{
    char	*str;
    int		j;

    j = 0;
    info->d_q = 0;
    info->s_q = 0;
    str = info->main_str;
    while (j <= i)
    {
        if (str[j] == 39)
        {
            info->last_quotes = 39;
            info->s_q++;
        }
        if (str[j] == 34)
        {
            info->last_quotes = 34;
            info->d_q++;
        }
        j++;
    }
}