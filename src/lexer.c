#include "minishell.h"

void    init_struct(t_lex *info, char *str)
{
	info->main_str = str;
	info->word_count = 0;
	info->strlen = ft_strlen((const char *)str);
	info->s_q = 0;
	info->d_q = 0;
	info->a = 0;
	info->b = 0;
}

int is_invalid_str(char *str, int i, int limit)
{
	if (i > 0 && i < limit - 1)
	{
		if ((str[i - 1] == 32 || is_rdrct(str, i - 1) != 0 || i == 1) && (str[i + 1] == 32 || is_rdrct(str, i + 1) != 0))
			return (1);
	}
	return (0);
}

int is_merge_quotes(char *str, int i, char pvt)
{
	if ((pvt == 34 || pvt == 39) && str[i] != 0 && str[i] == pvt)
		return (1);
	return (0);
}

int is_word_final_basic(char *str, int i)
{
	if ((str[i] != 32 && is_rdrct(str, i) == 0 && str[i] != '\0') &&
		(str[i + 1] == 32 || str[i + 1] == '\0' || is_rdrct(str, i) != 0))
	{
		// printf("char in is_word_final_basic : \' %c \' count: %d\n", str[i], i);
		return (1);
	}
	return (0);    
}

int  letter_counter_in_quotes(char *str, char pvt, int *i)
{
	int length;

	length = 0;
	while (is_merge_quotes(str, *i, pvt))
		*i += 2;
	(*i)++;
	while (str[*i] != pvt)
	{
		// printf("zz  %c  zz\n", str[*i]);
		length++;
		(*i)++;
	}
	if (is_merge_quotes(str, (*i) + 1, pvt))
	{
		*i += 2;
		// printf("HASSSKTR\n");
		letter_counter_in_quotes(str, pvt, i);
	}
	while (str[*i + 1] != 32 && str[*i + 1] != '\0' && is_rdrct(str, *i) == 0)
	{
		length++;
		(*i)++;
		if (str[*i] == 34 || str[*i] == 39)
			length += letter_counter_in_quotes(str, str[*i], i);
	}
	return (length);
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
			if (is_word_final_basic(str, j)) // eğer kelime bittiyse mallocla yer açılcak
			{
				// printf("!!!QUOTES -   word: %d   length: %d\n", current_wc, length);
				// line[current_wc] = malloc(sizeof(char) * (length + 2));
				line[current_wc] = ft_calloc(4, length + 2);
				length = 0;
				current_wc++;
				j++;
			}
		}
		else if (is_rdrct(str, j) == 1)
		{
			//printf("!!!SINGLE_REDIRECTION -   word: %ld\n", current_wc);
			// line[current_wc] = malloc(sizeof(char) * 3);
			line[current_wc] = ft_calloc(4, 3);
			current_wc++;
			j++;
			length = 0;
		}
		else if (is_rdrct(str, j) == 2)
		{
			//printf("!!!DOUBLE_REDIRECTION -   word: %ld\n", current_wc);
			// line[current_wc] = malloc(sizeof(char) * 4);
			line[current_wc] = ft_calloc(4, 4);
			// printf("zort%s\n", line[current_wc]);
			j += 2;
			current_wc++;
			length = 0;
		}
		else
		{
			length++;
			if (is_word_final_basic(str, j)) // eğer kelime bittiyse mallocla yer açılcak
			{
				//printf("!!!NORMAL_CHAR -  word: %ld  char: %c length: %ld\n", current_wc, str[j], length);
				j++;
				// line[current_wc] = malloc(sizeof(char) * (length + 2));
				// printf("found size of str %d: %d\n", current_wc, length);
				line[current_wc] = ft_calloc(4, length + 2);
				// printf("ZORT :: strlength of line %d: %d\n", current_wc, length);
				length = 0;
				current_wc++;
			}
			j++;
		}
		// printf("letter manager ------  %c\n", str[j]);
	}
}

// void	printf_control(t_lex *info)
// {
// 	printf
// }

char **lexer(char *str)
{
	t_lex	info;

	init_struct(&info, str);
	word_counter1(&info, info.main_str);
	// printf("%d\n", info.word_count);
	info.line = ft_calloc(sizeof(char *), (info.word_count + 1));
	letter_manager(&info, str, info.line);
	set_line(&info, str, info.line);
	// for (int i = 0; i < info.word_count; i++)
	// {
	// 	printf("line %d: %s\n", i, info.line[i]);
	// 	printf("strlength of line %d: %zu\n", i, ft_strlen(info.line[i]));
	// }
	return (info.line);
}
