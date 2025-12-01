/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:14:23 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/30 19:14:34 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
void print(t_list *lst)
{
	while(lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}
int main() 
{
	t_list *lst;
	lst = ft_lstnew("alo");
	lst ->next = ft_lstnew("hello");
	ft_lstadd_front(&lst, ft_lstnew("vova"));

	print(lst);
}*/
