#include "lexer.h"


void    init_struct(s_lex *info, char *str)
{

    info->main_str = str;
    info->strlen = ft_strlen(str);
    info->quotes_count = quotes_counter(info);
    printf("quotes count = %ld\n", info->quotes_count);
}

char **lexer(char *str)
{
    s_lex *info;

    info = malloc(sizeof(s_lex) * 2);
    init_struct(info, str);
    word_counter(info);
    printf("bulunan kelime sayisi = %ld\n", info->word_count);
    return (NULL);
}

int main()
{
    char str[] = "ls ''";
    printf("doğru kelime sayisi 6= \n");
    lexer(str);

    return (0);
}