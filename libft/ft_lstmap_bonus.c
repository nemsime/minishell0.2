/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:15:56 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/30 19:25:15 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new_list;

	if (!lst)
		return (NULL);
	res = NULL;
	while (lst)
	{
		if (f)
			new_list = ft_lstnew(f(lst->content));
		else
			new_list = ft_lstnew(lst->content);
		if (!new_list)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, new_list);
		lst = lst->next;
	}
	return (res);
}
