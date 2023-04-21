#include "minishell.h"

int  setter_in_quotes(t_lex *info, char *str, char *line, char pvt)
{
	info->ln->a++;
	while (str[info->ln->a] != pvt)
	{
		line[info->ln->b] = str[info->ln->a];
		info->ln->a++;
		(info->ln->b)++;
		if (str[info->ln->a] == pvt && str[info->ln->a + 1] == pvt)
			setter_in_quotes(info, (str + info->ln->a + 1), (line + info->ln->b), pvt);
	}
	info->ln->a++;
	if (str[info->ln->a] != 32 && str[info->ln->a] != 0 && is_rdrct(str, info->ln->a) == 0)
		return (0);
	return (1);
}

int  setter_rdirectn(t_lex *info, char *str, char *line)
{
	if (is_rdrct(str, info->ln->a) == 1)
	{
		line[info->ln->b] = str[info->ln->a];
		(info->ln->b)++;
		(info->ln->a)++;
	}
	else if (is_rdrct(str, info->ln->a) == 2)
	{
		line[info->ln->b] = str[info->ln->a];
		line[info->ln->b + 1] = str[info->ln->a + 1];
		info->ln->b += 2;
		info->ln->a += 2;
	}
	return (1);
}

int  setter_in_word(t_lex *info, char *str, char *line)
{
	// printf("line char : \"%d\"\n", ft_strlen(&line[info->ln->b]));
	while (str[info->ln->a] != 32 && str[info->ln->a] != 0 && is_rdrct(str, info->ln->a) == 0 &&
			str[info->ln->a] != 39 && str[info->ln->a] != 34)
	{
		// printf("line char : \"%d\"\n", line[info->ln->b]);
		printf("str char : \"%c\"\n", str[info->ln->b]);
		line[info->ln->b] = str[info->ln->a];
		info->ln->b += 1;
		info->ln->a += 1;
	}
	if (str[info->ln->a] != 32 && str[info->ln->a] != 0 && is_rdrct(str, info->ln->a) == 0)
	{
		return (0);
	}
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
	while (wd < info->word_count && str[info->ln->a] != 0)
	{
		printf("%d\n", wd);
		if (str[info->ln->a] == 32)
			info->ln->a++;
		else if (str[info->ln->a] == 34 || str[info->ln->a] == 39)
			// wd += setter_in_quotes(str, line[info->word_count], &i, str[i], &j);
			wd += setter_in_quotes(info, str, line[info->word_count], str[info->ln->a]);
		else if (is_rdrct(str, info->ln->a) > 0)
			wd += setter_rdirectn(info, str, line[info->word_count]);
		else if (32 < str[info->ln->a] && str[info->ln->a] < 127)
			wd += setter_in_word(info, str, line[info->word_count]);
	}
}
