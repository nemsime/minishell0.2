/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:24:28 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 14:05:33 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_2;
	unsigned char	*src_2;

	dest_2 = (unsigned char *)dest;
	src_2 = (unsigned char *)src;
	if (dest == 0 && src == 0)
		return (NULL);
	while (n != 0)
	{
		*dest_2++ = *src_2++;
		n--;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
	char dest[22];
	char src[] = "test UFAR aa, memcpy !";
	int alo[] = {1, 2, 3, 4, 5, 6, 8, 9, 0};
	int vaxo[10];

	char *res;
	char *res2;
	res = (char *)ft_memcpy(dest, src, 22);
	printf("%s\n", res);
	res2 = (char *)memcpy(dest, src, 22);
	printf("%s\n", res);

	int *res3;
	int *res4;
	res3 = (int *)ft_memcpy(vaxo, alo, 30);
	printf("\n%d\n", res3[8]);
	res4 = (int *)memcpy(vaxo, alo, 30);
	printf("%d\n", res4[8]);


	int *res5;
	int *res6;
	res5 = (int *)ft_memcpy("    ", ((void *)0), 3);
	printf("\n%d\n", *res5);
	res6 = (int *)memcpy("     ", ((void *)0), 3);
	printf("%d\n", *res6);
}*/
