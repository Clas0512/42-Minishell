#include "minishell.h"

int    is_rdrct(char *str, int i)
{
    char    c;

    c = str[i];
    if (c == '&' && str[i + 1] == '&')
        return (2);
    if (c == '|' || c == '<' || c == '>')
    {
        if (str[i + 1] == c && str[i + 1] != '&')
        {
            return (2);
        }
    //    printf("aftr %d\n", i);
        return (1);
    }
    return (0);
}

int is_valid_dollar(s_lex *info, int i)
{
    char    *str;

    str = info->main_str;
    if (!(((info->s_q % 2 == 1) && (info->d_q % 2 == 1) && (info->last_quotes == 34)) ||
		((info->s_q % 2 == 1) && (info->d_q % 2 == 0))) &&
		(str[i] == '$' && ((str[i + 1] >= 'a' && str[i + 1] <= 'z') ||
        (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))))
        return (1);
    return (0);
}

int word_control_1(s_lex *info, int i)
{
    if ((info->d_q % 2 == 0) && (info->s_q % 2 == 0) && (str[i] != ' ') &&
            (str[i + 1] == '\0' || str[i + 1] == ' ' ||
            is_rdrct(info->main_str, i + 1)))
        return (1);
    return (0);
}

void    quotes_counter(s_lex *info, int i)
{
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

void    word_counter(s_lex *info)
{
    int    i;
    char    *str;

    info->d_q = 0;
    info->s_q = 0;
    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        quotes_counter(info, i);
        //if (is_valid_dollar(info, i))
        //    info->word_count++;
        //printf("%d - %ld\n", is_rdrct(info->main_str, &i + 1), i);
        if (word_control_1(info, i))
        {
            
			printf("!q %c %d\n", str[i], i);
			if (is_rdrct(info->main_str, i) == 2)
				i++;
			info->word_count++;
			if ((str[i] == 34 && str[i - 1] == 34) || (str[i] == 39 && str[i - 1] == 39))
			{
				printf("!Q %c %d\n", str[i], i);
				info->word_count--;
			}
		}
		else if ((info->d_q % 2 == 0) && (info->s_q % 2 == 0) && is_rdrct(info->main_str, i) && !is_rdrct(info->main_str, i + 1))
		{
			printf("!e %c %d\n", str[i], i);
			info->word_count++;
		}
		i++;
	}
    info->d_q = 0;
    info->s_q = 0;
}
