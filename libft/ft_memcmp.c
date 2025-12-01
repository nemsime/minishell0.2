/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:22:56 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:22:58 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (n--)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
	char *s1 = "\xff\xaa\xde\x11";
	char *s2 = "";
	size_t size = 20;
	printf("%d\n", memcmp(s1, s2, size));
	printf("%d\n", ft_memcmp(s1, s2, size));
}*/
