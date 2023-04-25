#include "minishell.h"

int    is_rdrct(char *str, int i)
{
    char    c;

    c = str[i];
    if (c == '&' && str[i + 1] == '&')
        return (2);
    if (c == '|' || c == '<' || c == '>')
    {
        if (str[i + 1] == c && str[i + 1] != '&')
            return (2);
        return (1);
    }
    return (0);
}

int is_valid_dollar(t_lex *info, int i)
{
    char    *str;

    str = info->main_str;
    if (!(((info->s_q % 2 == 1) && (info->d_q % 2 == 1) && (info->last_quotes == 34)) ||
        ((info->s_q % 2 == 1) && (info->d_q % 2 == 0))) && (str[i] == '$' &&
        ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= 'A' && str[i + 1] <= 'Z'))))
        return (1);
    return (0);
}

int word_control_1(t_lex *info, int i)
{
    char *str;

    str = info->main_str;
    if ((info->d_q % 2 == 0) && (info->s_q % 2 == 0) && (str[i] != ' ') &&
            (str[i + 1] == '\0' || str[i + 1] == ' ' ||
            is_rdrct(info->main_str, i + 1)))
        return (1);
    return (0);
}

void    invld_quotes_str(t_lex *info)
{
    int  i;
    char *str;

    str = info->main_str;
    i = 0;
    while (str[i] != '\0')
    {
        quotes_counter(info, i);
        if ((i == 0 || str[i] == 32) && (str[i + 1] == 34 || str[i + 1] == 39))
        {
            i++;
            quotes_counter(info, i);
            if ((info->d_q % 2 == 1) && (i < info->strlen - 1) && str[i] == 34 && str[i + 1] == 34 &&
                (str[i + 2] == '\0' || str[i + 2] == 32) && str[i + 2] != 34)
                {
                    // printf("invalid_str1 -- %ld\n", i);
                    info->word_count--;
                }
            else if ((info->s_q % 2 == 1) && (i < info->strlen - 1) && str[i] == 39 && str[i + 1] == 39 &&
                (str[i + 2] == '\0' || str[i + 2] == 32) && str[i + 2] != 39)
                {
                    // printf("invalid_str2 -- %ld\n", i);
                    info->word_count--;
                }
        }
        i++;
    }
}

////////////////////////////
int word_passer(char *str, int *i)
{
    while (str[*i + 1] != '\0' && str[*i + 1] != 32 && is_rdrct(str, *i + 1) == 0)
        (*i)++;
    return (1);
}

int    quotes_passer(char *str, int *i, char pvt)
{
    int q;

    q = 0;
    if (str[*i + 1] == pvt && (str[*i + 2] == 32 || str[*i + 2] == '\0'))
    {
        *i += 1;
        return (1);
    }
    while (!(q % 2 == 0 && (str[*i + 1] == 32 || str[*i + 1] == '\0')))
    {
        q = quotes_counter_spcl(str, pvt, *i);
        if (is_merge_quotes(str, *i + 1, str[*i]))
        {
            // printf("check letter for is_merge_quotes if : \"%c\"     ------       i = %d\n", str[*i], *i);    
            // printf("%d\n", (*i));
            // printf("ZORTINGEN\n");
            (*i)++;
            word_passer(str, i);
        }
        *i += 1;
        if (str[*i] == '\0')
            return (1);
        // printf("check letter for q : \"%c\"     ------       i = %d\n", str[*i], *i);
        // printf("-*- q = %d -*-\n", q);
    }
    // printf("quotes_passer: %c in %ld\n", str[*i], *i);
    return (1);
}


void    word_counter1(t_lex *info, char *str)
{
    int i;

    i = 0;
    while (i < info->strlen && str[i] != '\0')
    {
        // printf("*** %d ***\n", info->strlen);
        // exit(1);
        // printf("-*- %c -*- detected by word_COUNTER1 func and word count = %d\n", str[i], info->word_count);
        if (str[i] == 32)
            i++;
        else if (str[i] == 34 || str[i] == 39)
        {
            info->word_count += quotes_passer(str, &i, str[i]);
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
    // printf("\nbulunan kelime sayisi = %d\n", info->word_count);
}