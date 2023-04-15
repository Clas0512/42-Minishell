#include "minishell.h"

void    init_struct(s_lex *info, char *str)
{
    info->last_quotes = 0;
    info->main_str = str;
    info->strlen = ft_strlen(str);
	info->sgn_lst = malloc(sizeof(int) * info->strlen);
    quotes_counter(info);
    printf("single quotes count = %ld\n", info->s_q);
    printf("double quotes count = %ld\n", info->d_q);
}

size_t letter_counter(s_lex *info)
{
    size_t i;
    size_t length;
    int signd;
    char *str;

    signd = 0;
    str = info->main_str;
    length = 0;
    i = 0;
    if (word_control_1(info, i))
    {
        length = i;
        while (i >= 0)
        {
            quotes_counter(info, i);
            if (info->s_q >= 1 || info->d_q >= 1)
                
            length -= 2;
        }
        i++;
    }
    return (length);
}

char **lexer(char *str)
{
    s_lex *info;
    char **line;
    int i;

    info = malloc(sizeof(s_lex) * 2);
    init_struct(info, str);
    word_counter(info);
    line = malloc(sizeof(char *) * info->word_count + 1);
    i = 0;
    while (line[i] != '\0')
    {
        line[i] = malloc(sizeof(char) * letter_counter(info) + 1);
        i++;
    }
    printf("bulunan kelime sayisi = %ld\n", info->word_count);
    return (NULL);
}
