#include "minishell.h"

void    init_struct(s_lex *info, char *str)
{
    info->last_quotes = 0;
    info->main_str = str;
    info->strlen = ft_strlen(str);
	info->sgn_lst = malloc(sizeof(int) * info->strlen);
    //quotes_current_count(info, i);
    printf("single quotes count = %ld\n", info->s_q);
    printf("double quotes count = %ld\n", info->d_q);
}

size_t letter_counter(s_lex *info)
{
    static size_t i;
    size_t length;
    static size_t j;
    char *str;

	length = 0;
    str = info->main_str;
	while (str[j] == 32 && i < info->word_count)
		j++;
	while (!word_control_1(info, j))
	{
		quotes_current_count(info, j);
		//printf("counting letter -- ' %c '\n", str[j]);
		j++;
		length++;
	}
	if (info->s_q >= 1 || info->d_q >= 1)
	{
		if (info->last_quotes == 34)
			length -= info->d_q;
		else
			length -= info->s_q;
	}
	j++;
	i++;
	//printf("length of word %zu is -> %zu\n", i, length);
    return (length);
}

char **lexer(char *str)
{
    s_lex *info;
    char **line;
    size_t i;

    info = malloc(sizeof(s_lex) * 2);
    init_struct(info, str);
    word_counter(info);
    line = malloc(sizeof(char *) * info->word_count + 1);
    i = 0;
    while (i < info->word_count)
    {
        line[i] = malloc(sizeof(char) * letter_counter(info) + 1);
        i++;
    }
    printf("bulunan kelime sayisi = %ld\n", info->word_count);
    return (NULL);
}
