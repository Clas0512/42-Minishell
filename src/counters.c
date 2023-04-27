#include "minishell.h"

int  letter_counter_in_quotes(char *str, char pvt, int *i)
{
	int length;

	length = 0;
	(*i)++;
	while (str[*i] != pvt)
	{
		length++;
		(*i)++;
	}
	(*i)++;
	if (str[*i] == 34 || str[*i] == 39)
		length += letter_counter_in_quotes(str, str[*i], i);
	return (length);
}
