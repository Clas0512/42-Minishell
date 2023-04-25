#include "minishell.h"

void	quotes_counter(t_lex *info, int i)
{
	char	*str;
	int		j;

	j = 0;
	info->d_q = 0;
	info->s_q = 0;
	str = info->main_str;
	while (j <= i)
	{
		if (str[j] == 39)
		{
			info->last_quotes = 39;
			info->s_q++;
		}
		if (str[j] == 34)
		{
			info->last_quotes = 34;
			info->d_q++;
		}
		j++;
	}
}

int	quotes_counter_spcl(char *str, char pvt, int i)
{
	int	r;

	r = 0;
	while (i >= 0)
	{
		// printf("\"%c\" in %d \n", str[i], i);
		if (str[i] == pvt)
			r++;
		i--;
	}
	return (r);
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
    while (!(q % 2 == 0 && (str[*i] == 32 || str[*i] == '\0')))
    {
        // printf("found char \"%c\" in %d and q = %d\n", str[*i], *i, q);
        q = quotes_counter_spcl(str, pvt, *i);
        if (is_merge_quotes(str, *i + 1, str[*i]))
        {
            // printf("found a merge quotes\n");
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

int	is_merge_quotes(char *str, int i, char pvt)
{
	if ((pvt == 34 || pvt == 39) && str[i] != 0 && str[i] == pvt)
		return (1);
	return (0);
}