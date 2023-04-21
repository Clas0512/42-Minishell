#include "minishell.h"

int  setter_in_quotes(char *str, char *line, int *i, char pvt, int *j)
{
    (*i)++;
    while (str[*i] != pvt)
    {
        line[*j] = str[*i];
        (*i)++;
        (*j)++;
        if (str[*i] == pvt && str[*i + 1] == pvt)
            setter_in_quotes((str + *i + 1), (line + *j), i, pvt, j);
    }
    (*i)++;
    if (str[*i] != 32 && str[*i] != 0 && is_rdrct(str, *i) == 0)
        return (0);
    return (1);
}

int  setter_rdirectn(char *str, char *line, int *i, int *j)
{
    if (is_rdrct(str, *i) == 1)
    {
        line[*j] = str[*i];
        (*j)++;
        (*i)++;
    }
    else if (is_rdrct(str, *i) == 2)
    {
        line[*j] = str[*i];
        line[*j + 1] = str[*i + 1];
        *j += 2;
        *i += 2;
    }
    return (1);
}

int  setter_in_word(char *str, char *line, int *i, int *j)
{
    printf("line char : \"%c\"\n", line[*j]);
    while (str[*i] != 32 && str[*i] != 0 && is_rdrct(str, *i) == 0 &&
            str[*i] != 39 && str[*i] != 34)
    {
        printf("line char : \"%d\"\n", line[*j]);
        printf("str char : \"%c\"\n", str[*j]);
        line[*j] = str[*i];
        (*j)++;
        (*i)++;
    }
    if (str[*i] != 32 && str[*i] != 0 && is_rdrct(str, *i) == 0)
    {
        return (0);
    }
    return (1);
}

void    set_line(s_lex *info, char *str, char **line)
{
    int i;
    int j;
    int wd;

    wd = 0;
    j = 0;
    i = 0;
    while (wd < info->word_count && str[i] != 0)
    {
        printf("%d\n", wd);
        if (str[i] == 32)
            i++;
        else if (str[i] == 34 || str[i] == 39)
            wd += setter_in_quotes(str, line[info->word_count], &i, str[i], &j);
        else if (is_rdrct(str, i) > 0)
            wd += setter_rdirectn(str, line[info->word_count], &i, &j);
        else if (32 < str[i] && str[i] < 127)
            wd += setter_in_word(str, line[info->word_count], &i, &j);
    }
}
