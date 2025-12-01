/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:11:41 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/30 19:13:11 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	make_string(char *res, int nb, int len)
{
	res[len] = '\0';
	while (len--)
	{
		res[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	nb;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		nb = -n;
	else
		nb = n;
	len = ft_len(n);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	make_string(res, nb, len);
	if (n < 0)
		res[0] = '-';
	return (res);
}
/*
#include <stdio.h>
#include <string.h>
void	print_result(int success)
{
	if (success)
		printf("ok \n");
	else
		printf("qaq\n");
}

int	main()
{
	char *result;
	result = ft_itoa(-2147);
	printf("%s\n", result);
	print_result(strcmp(result, "-2147") == 0);
	free(result);
}*/
