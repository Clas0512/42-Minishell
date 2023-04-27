#include "minishell.h"

int  setter_in_quotes(t_lex *info, char *str, char *line, char pvt)
{
	info->last_quotes = pvt;
	info->a++;
	while (str[info->a] != pvt)
	{
		line[info->b] = str[info->a];
		info->a++;
		info->b++;
	}
	info->a++;
	if (str[info->a] == pvt)
		setter_in_quotes(info, str, line, pvt);
	if (str[info->a] != 32 && str[info->a] != 0 && is_rdrct(str, info->a) == 0)
		return (0);
	return (1);
}

int  setter_rdirectn(t_lex *info, char *str, char *line)
{
	if (is_rdrct(str, info->a) == 1)
	{
		line[info->b] = str[info->a];
		(info->b)++;
		(info->a)++;
	}
	else if (is_rdrct(str, info->a) == 2)
	{
		line[info->b] = str[info->a];
		line[info->b + 1] = str[info->a + 1];
		info->b += 2;
		info->a += 2;
	}
	return (1);
}

int  setter_in_word(t_lex *info, char *str, char *line)
{
	while (str[info->a] != 32 && str[info->a] != 0 && is_rdrct(str, info->a) == 0 &&
			str[info->a] != 39 && str[info->a] != 34)
	{
		line[info->b] = str[info->a];
		info->b += 1;
		info->a += 1;
	}
	if (str[info->a] != 32 && str[info->a] != 0 && is_rdrct(str, info->a) == 0)
		return (0);
	return (1);
}

void    set_line(t_lex *info, char *str, char **line)
{
	int wd;
	int	wd_past;

	wd = 0;
	while (wd < info->word_count && str[info->a] != '\0')
	{
		wd_past = wd;
		if (str[info->a] == 32)
			info->a++;
		else if (str[info->a] == 34 || str[info->a] == 39)
		{
			wd += setter_in_quotes(info, str, line[wd], str[info->a]);
			if (wd_past != wd)
				tokenize_q_str(info, wd_past, 'C');
		}
		else if (is_rdrct(str, info->a) > 0)
		{
			wd += setter_rdirectn(info, str, line[wd]);
			if (wd_past != wd)
				tokenize_q_str(info, wd_past, 'M');
		}
		else if (32 < str[info->a] && str[info->a] < 127)
		{
			wd += setter_in_word(info, str, line[wd]);
			if (wd_past != wd)
				tokenize_q_str(info, wd_past, 'C');
		}
	}
}
