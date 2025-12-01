/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:57 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:32:00 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
			res = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (res);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char str[] = "hello wolrd.";
	printf("%s\n", ft_strrchr(str, 'o'));
	printf("%s\n", strrchr(str, 'o'));
}*/
