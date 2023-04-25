#include "minishell.h"

int  setter_in_quotes(t_lex *info, char *str, char *line, char pvt)
{
	info->a++;
	// printf("-*- %c -*-\n", str[info->b]);
	// printf("-*- %c -*-\n", line[info->b]);
	while (str[info->a] != pvt)
	{
		// printf("------> line c: %d   str c: %d\n", info->b, info->a);
		line[info->b] = str[info->a];
		info->a++;
		info->b++;
		// if (str[info->a] == pvt && is_merge_quotes(str, info->a + 2))
		// 	setter_in_quotes(info, str, line, pvt);
	}
	info->a++;
	if (str[info->a] == pvt)
		setter_in_quotes(info, str, line, pvt);
	// printf("str: %s\n", line);
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
	// printf("line char : \"%d\"\n", ft_strlen(&line[info->ln->b]));
	while (str[info->a] != 32 && str[info->a] != 0 && is_rdrct(str, info->a) == 0 &&
			str[info->a] != 39 && str[info->a] != 34)
	{
		// printf("str char : \"%c\"\n", str[info->a]);
		// printf("old line char : \"%c\"\n", line[info->b]);
		line[info->b] = str[info->a];
		// printf("new line char : \"%c\"\n\n", line[info->b]);
		info->b += 1;
		info->a += 1;
	}
	// printf("strlength of line : %zu  -*-*- str is : \"%s\" \n", ft_strlen(line), line);
	if (str[info->a] != 32 && str[info->a] != 0 && is_rdrct(str, info->a) == 0)
		return (0);
	return (1);
}

void    set_line(t_lex *info, char *str, char **line)
{
	int wd;

	wd = 0;
	// for (size_t i = 0; line[i] != NULL; i++)
	// {
	// 	printf("a%lu\n", sizeof(line[i]));
	// }
	while (wd < info->word_count && str[info->a] != 0)
	{
		if (str[info->a] == 32)
			info->a++;
		else if (str[info->a] == 34 || str[info->a] == 39)
			// wd += setter_in_quotes(str, line[info->word_count], &i, str[i], &j);
		{
			wd += setter_in_quotes(info, str, line[wd], str[info->a]);
			info->b = 0;
		}
		else if (is_rdrct(str, info->a) > 0)
		{
			wd += setter_rdirectn(info, str, line[wd]);
			info->b = 0;
		}
		else if (32 < str[info->a] && str[info->a] < 127)
		{
			// printf("wd: %d -- char: %c\n", wd, str[info->a]);
			wd += setter_in_word(info, str, line[wd]);
			info->b = 0;
		}
	}
	// for (int i = 0; i < info->word_count; i++)
	// {
	// 	printf("line %d: %s\n", i, info->line[i]);
	// 	printf("strlength of line %d: %zu\n", i, ft_strlen(info->line[i]));
	// }
}
