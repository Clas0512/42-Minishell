#include "minishell.h"

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
