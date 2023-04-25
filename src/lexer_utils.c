#include "minishell.h"

int is_valid_dollar(t_lex *info, int i)
{
    char    *str;

    str = info->main_str;
    if (!(((info->s_q % 2 == 1) && (info->d_q % 2 == 1) && (info->last_quotes == 34)) ||
        ((info->s_q % 2 == 1) && (info->d_q % 2 == 0))) && (str[i] == '$' &&
        ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))))
        return (1);
    return (0);
}

int    is_rdrct(char *str, int i)
{
    char    c;

    c = str[i];
    if (c == '&' && str[i + 1] == '&')
        return (2);
    if (c == '|' || c == '<' || c == '>')
    {
        if (str[i + 1] == c && str[i + 1] != '&')
            return (2);
        return (1);
    }
    return (0);
}

int word_control_1(t_lex *info, int i)
{
    char *str;

    str = info->main_str;
    if ((info->d_q % 2 == 0) && (info->s_q % 2 == 0) && (str[i] != ' ') &&
            (str[i + 1] == '\0' || str[i + 1] == ' ' ||
            is_rdrct(info->main_str, i + 1)))
        return (1);
    return (0);
}

int word_passer(char *str, int *i)
{
    while (str[*i + 1] != '\0' && str[*i + 1] != 32 && is_rdrct(str, *i + 1) == 0)
        (*i)++;
    return (1);
}

int is_word_final_basic(char *str, int i)
{
	if ((str[i] != 32 && is_rdrct(str, i) == 0 && str[i] != '\0') &&
		(str[i + 1] == 32 || str[i + 1] == '\0' || is_rdrct(str, i) != 0))
		return (1);
	return (0);    
}