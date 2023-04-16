#include "minishell.h"

void    quotes_current_count(s_lex *info, int i)
{
	char *str;

	str = info->main_str;
    if (str[i] == 39)
    {
        info->last_quotes = 39;
        info->s_q++;
    }
    if (str[i] == 34)
    {
        info->last_quotes = 34;
        info->d_q++;
    }
}