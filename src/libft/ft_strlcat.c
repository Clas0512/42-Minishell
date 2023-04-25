/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 04:29:29 by aerbosna          #+#    #+#             */
/*   Updated: 2023/03/03 04:55:41 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	leng_dst;
	size_t	leng_src;
	size_t	i;
	size_t	limit;

	leng_dst = ft_strlen(dst);
	leng_src = ft_strlen((const char *)src);
	if (dst_size <= leng_dst)
		return (dst_size + leng_src);
	i = 0;
	limit = leng_dst;
	while (src[i] && i < (dst_size - leng_dst - 1))
		dst[limit++] = src[i++];
	dst[limit] = '\0';
	return (leng_dst + leng_src);
}
