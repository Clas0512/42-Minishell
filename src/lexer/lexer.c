#include "minishell.h"


void    init_struct(s_lex *info, char *str)
{

    info->main_str = str;
    info->strlen = ft_strlen(str);
    quotes_counter(info);
    printf("single quotes count = %ld\n", info->s_quotes_count);
    printf("double quotes count = %ld\n", info->d_quotes_count);
}

char **lexer(char *str)
{
    s_lex *info;

    info = malloc(sizeof(s_lex) * 2);
    init_struct(info, str);
    word_counter(info);
    printf("bulunan kelime sayisi = %ld\n", info->word_count);
    printf("%s\n", (char *)info->main_str);
    return (NULL);
}
