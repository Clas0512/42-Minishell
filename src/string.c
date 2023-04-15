// #include "minishell.h"

// size_t	length(char *string)
// {
// 	size_t	index;

// 	index = 0;
// 	while (string[index] != '\0')
// 		index++;
// 	return (index);
// }

// size_t	array_length(char **strings)
// {
// 	size_t index;
// 	size_t total_length;

// 	index = 0;
// 	total_length = 0;
// 	while (strings[index] != NULL)
// 	{
// 		total_length += len(strings[index]);
// 		index++;
// 	}
// 	return (total_length);
// }

// char *duplicate(char *string)
// {
// 	char			*new;
// 	t_collection	*collection;

// 	new = malloc(sizeof(char) * (length(string) + 1));
// 	collection = create_collection(new);
// 	add_collection(&shell.collector. new);
// 	return (new);
// }


// char *join(char **strings)
// {
// 	char	*joined;
// 	size_t	joined_index;
// 	size_t	string_index;
// 	size_t	array_index;

// 	joined = malloc(sizeof(char) * (array_length(strings) + 1));
// 	joined_index = 0;
// 	array_index = 0;
// 	while (strings[array_index] != NULL)
// 	{
// 		string_index = 0;
// 		while (strings[array_index][string_index] != '\0')
// 		{
// 			joined[joined_index] = strings[array_index][string_index];
// 			string_index++;
// 		}
// 		array_index++;
// 	}
// 	joined[joined_index] = '\0';
// 	return (joined);
// }
