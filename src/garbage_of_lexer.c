#include "minishell.h"

int is_invalid_str(char *str, int i, int limit)
{
	if (i > 0 && i < limit - 1)
	{
		if ((str[i - 1] == 32 || is_rdrct(str, i - 1) != 0 || i == 1) && (str[i + 1] == 32 || is_rdrct(str, i + 1) != 0))
			return (1);
	}
	return (0);
}

void    invld_quotes_str(t_lex *info)
{
    int  i;
    char *str;

    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        quotes_counter(info, i);
        if ((i == 0 || str[i] == 32) && (str[i + 1] == 34 || str[i + 1] == 39))
        {
            i++;
            quotes_counter(info, i);
            if ((info->d_q % 2 == 1) && (i < info->strlen - 1) && str[i] == 34 && str[i + 1] == 34 &&
                (str[i + 2] == '\0' || str[i + 2] == 32) && str[i + 2] != 34)
                    info->word_count--;
            else if ((info->s_q % 2 == 1) && (i < info->strlen - 1) && str[i] == 39 && str[i + 1] == 39 &&
                (str[i + 2] == '\0' || str[i + 2] == 32) && str[i + 2] != 39)
                    info->word_count--;
        }
        i++;
    }
}