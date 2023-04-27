#include "minishell.h"

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

void    init_struct(t_lex *info, char *str)
{
	info->main_str = str;
	info->word_count = 0;
	info->strlen = ft_strlen((const char *)str);
	info->s_q = 0;
	info->d_q = 0;
	info->a = 0;
	info->b = 0;
	info->error = false;
	info->error_str = malloc(sizeof(char *) * 2);
	info->error_str[0] = ft_strdup("ERROR");
}

void letter_manager(t_lex *info, char *str, char **line)
{
	int length;
	int current_wc;
	int j;

	current_wc = 0;
	j = 0;
	length = 0;
	while (current_wc < info->word_count && j < info->strlen)
	{
		if (str[j] == 32) // boşlukları atlama
			j++;
		else if (str[j] == 34 || str[j] == 39) // tırnak mı? Değil mi?
		{
			length += letter_counter_in_quotes(str, str[j], &j); // karakterleri sayma fonksiyonundan dönen değeri length değişkenine atma
			// printf("length :%d \n", length);
			if (is_word_final_quotes(str, j)) // eğer kelime bittiyse mallocla yer açılcak
			{
				line[current_wc] = ft_calloc(4, length + 2);
				length = 0;
				current_wc++;
			}
		}
		else if (is_rdrct(str, j) == 1)
		{
			line[current_wc] = ft_calloc(4, 3);
			current_wc++;
			j++;
			length = 0;
		}
		else if (is_rdrct(str, j) == 2)
		{
			line[current_wc] = ft_calloc(4, 4);
			j += 2;
			current_wc++;
			length = 0;
		}
		else
		{
			length++;
			j++;
			if (is_word_final_basic(str, j)) // eğer kelime bittiyse mallocla yer açılcak
			{
				line[current_wc] = ft_calloc(4, length + 2);
				length = 0;
				current_wc++;
			}
		}
	}
}

void    word_manager(t_lex *info, char *str)
{
    int i;

    i = 0;
    while (i < info->strlen && str[i] != '\0')
    {
        // printf("*** %d ***\n", info->strlen);
        // exit(1);
        // printf("-*- %c -*- detected in %d and word count = %d\n", str[i], i, info->word_count);
        if (str[i] == 32)
            i++;
        else if (str[i] == 34 || str[i] == 39)
        {
            // printf("before quotes passer %d\n", i);
            info->word_count += quotes_passer(str, &i, str[i]);
            // printf("after quotes passer %d\n", i);
            if (str[i] == '\0')
            while (str[i] != 32 && str[i] != '\0' && is_rdrct(str, i) != 0)
                i++;
        }
        else if (is_rdrct(str, i) == 1)
        {
            i++;
            info->word_count++;
        }
        else if (is_rdrct(str, i) == 2)
        {
            i += 2;
            info->word_count++;
        }
        else
        {
            info->word_count += word_passer(str, &i);
            i++;
        }
    }
    // printf("bulunan kelime sayisi = %d\n", info->word_count);
}

char **lexer(char *str)
{
	t_lex	info;

	init_struct(&info, str);
	check_error(&info, info.main_str);
	// printf("info.error = %d\n", info.error);
	if (info.error == true)
		return (info.error_str);
	word_manager(&info, info.main_str);
	info.flags = malloc(sizeof(char) * (info.word_count + 1));
	// printf("%d\n", info.word_count);
	info.line = ft_calloc(sizeof(char *), (info.word_count + 1));
	letter_manager(&info, str, info.line);
	set_line(&info, str, info.line);
	// for (int i = 0; i < info.word_count; i++)
	// {
	// 	printf("line %d: %s\n", i, info.line[i]);
	// 	printf("strlength of line %d: %zu\n", i, ft_strlen(info.line[i]));
	// }
	// for (int i = 0; i < info.word_count; i++)
	// 	printf("word %d :: %c\n", i, info.flags[i]);
	return (info.line);
}
