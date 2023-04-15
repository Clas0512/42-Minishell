/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 02:43:27 by aerbosna          #+#    #+#             */
/*   Updated: 2023/03/03 09:14:06 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dst;
	int		i;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen((const char *)s);
	if (len > len_s)
		len = len_s;
	if (start >= len_s)
		return ((char *)ft_calloc(sizeof(char), 1));
	i = 0;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (len-- && s[i + (int)start])
	{
		dst[i] = s[i + start];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
