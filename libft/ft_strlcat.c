/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:29:18 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:29:21 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	int		i;

	i = 0;
	if ((!src || !dst) && dstsize == 0)
		return (0);
	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	while (src[i] && (len_dest + i < dstsize - 1))
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = 0;
	if (len_dest + i < dstsize)
		return (len_dest + len_src);
	return (dstsize + len_src);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char dest[] = "Hello !";
	int	arg;

	printf("%s", dest);
	printf("\n%zu", ft_strlcat(dest, "lorem", 0));
	
	printf("\n%s", dest);
}*/
