#include "minishell.h"

void    init_struct(t_lex *info, char *str)
{
	info->main_str = str;
	info->word_count = 0;
	info->last_quotes_count = 0;
	info->strlen = ft_strlen((const char *)str);
	info->s_q = 0;
	info->d_q = 0;
	info->a = 0;
	info->b = 0;
	info->error = false;
	info->error_str[0] = NULL;
}

void	check_error(t_lex *info, char *str)
{
	int		i;
	char	pvt;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
		{
			pvt = str[i];
			info->last_quotes_count = i;
			while (str[++i] != pvt)
			{
				if (str[i] == '\0')
				{
					info->error = true;
					return ;
				}
			}
		}
	}
}

void	init_manager_struct(t_lex *info)
{
	info->manager.length = 0;
	info->manager.current_wc = 0;
	info->manager.j = 0;
	info->manager.r = 0;
}

void letter_manager(t_lex *info, char *str)
{
	while (info->manager.current_wc < info->word_count && info->manager.j < info->strlen)
	{
		info->manager.r = 0;
		info->manager.r = is_rdrct(str, info->manager.j);
		if (str[info->manager.j] == 32)
			info->manager.j++;
		else if (str[info->manager.j] == 34 || str[info->manager.j] == 39)
		{
			info->manager.length += letter_counter_in_quotes(str, str[info->manager.j], &info->manager.j);
			if (is_word_final_quotes(str, info->manager.j))
				helper(info, info->manager.r, 0);
		} 
		else if (info->manager.r != 0)
			helper(info, info->manager.r, 'r');
		else
		{
			info->manager.length++;
			info->manager.j++;
			if (is_word_final_basic(str, info->manager.j))
				helper(info, info->manager.r, 0);
		}
	}
}

void	helper(t_lex *info, int r, char mod)
{
	if (mod == 'r')
	{
		info->line[info->manager.current_wc] = ft_calloc(4, r + 1);
		info->manager.j += r;
	}
	else
		info->line[info->manager.current_wc] = ft_calloc(4, (info->manager.length) + 2);
	info->manager.length = 0;
	info->manager.current_wc++;
}

void	space_jumper(char *str, int *i)
{
	if (str[*i] == 32)
		(*i)++;
}

void    word_manager(t_lex *info, char *str)
{
    int	i;
	static int	r;

	i = 0;
    while (i < info->strlen && str[i] != '\0')
    {
		r = is_rdrct(str, i);
		space_jumper(str, &i);
		if (str[i] == 34 || str[i] == 39)
        {
            info->word_count += quotes_passer(str, &i, str[i]);
            while (str[i] != 32 && str[i] != '\0' && is_rdrct(str, i) == 0)
                i++;
        }
		else if (r != 0)
		{
			i += r;
			info->word_count++;
		}
        else
        {
            info->word_count += word_passer(str, &i);
            i++;
        }
    }
	// printf("word count : %d\n", info->word_count);
}

void	change_main_str(t_lex *info)
{
	int		i;
	int		j;
	char	*str;

	str = ft_calloc(ft_strlen(info->main_str), sizeof(char));
	i = 0;
	j = 0;
	while (info->main_str[i] != '\0')
	{
		if (i == info->last_quotes_count)
			i++;
		str[j] = info->main_str[i];
		if (info->main_str[i] == '\0')
			break;
		i++;
		j++;
	}
	free(info->main_str);
	info->main_str = str;
}

char **lexer(char *str)
{
	t_lex	info;

	init_struct(&info, str);
	check_error(&info, info.main_str);
	if (info.error == true)
	{
		change_main_str(&info);
		info.strlen = ft_strlen((const char *)info.main_str);
	}
	word_manager(&info, info.main_str);
	info.flags = malloc(sizeof(char) * (info.word_count + 1));
	// printf("wc : %d\n", info.word_count);
	info.line = ft_calloc(sizeof(char *), (info.word_count + 1));
	init_manager_struct(&info);
	letter_manager(&info, info.main_str);
	init_manager_struct(&info);
	set_line(&info, info.main_str, info.line);
	return (info.line);
}
