#include "minishell.h"

void    init_struct(s_lex *info, char *str)
{
    info->main_str = str;
    printf("-*-*-*-*-*-*--*- %p -*--*-*-*-*-*-*-\n", &info->s_q);
    info->strlen = ft_strlen((const char *)str);
    info->s_q = 0;
    info->d_q = 0;
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
    if ((pvt == 34 || pvt == 39) && str[i + 1] == pvt)
        return (1);
    return (0);
}

int is_word_final_basic(char *str, int i)
{
    if ((str[i] != 32 && is_rdrct(str, i) == 0 && str[i] != '\0') &&
        (str[i + 1] == 32 || str[i + 1] == '\0' || is_rdrct(str, i) != 0))
            return (1);
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
        length++;
        (*i)++;
    }
    if (is_merge_quotes(str, (*i) + 1, pvt))
    {
        *i += 2;
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

void letter_manager(s_lex *info, char *str, char **line)
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
                // printf("!!!QUOTES -   word: %ld   length: %ld\n", current_wc, length);
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
                line[current_wc] = ft_calloc(4, length + 2);
                length = 0;
                current_wc++;
            }
            j++;
        }
        // printf("letter manager ------  %c\n", str[j]);
    }
}

char **lexer(char *str)
{
    s_lex   info;
    char    **line;
    int i;

    init_struct(&info, str);
    word_counter1(&info, info.main_str);
    line = malloc(sizeof(char *) * (info.word_count + 3));
    letter_manager(&info, str, line);
    set_line(&info, str, line);
    i = 0;
    while (i < info.word_count)
    {
        while (line[i] != 0)
            printf("%s\n", line[i]);
        i++;
    }
    return (line);
}
