/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerbosna <aerbosna@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:43:35 by aerbosna          #+#    #+#             */
/*   Updated: 2023/03/14 07:43:54 by aerbosna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_map;
	t_list	*new;

	lst_map = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new)
			ft_lstadd_back(&lst_map, new);
		else
			ft_lstclear(&new, del);
		lst = lst->next;
	}
	return (lst_map);
}
