/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:28:43 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:28:46 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p++ = (unsigned char)c;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>
int	main()
{
	char *str = (char *)malloc(sizeof(char) * 10);

	str[9] = 0;
	ft_memset(str, 'a', 11);
	printf("%s\n", (char *)str);
	free(str);
}*/
