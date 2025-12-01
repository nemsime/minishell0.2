/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:17:03 by szakarya          #+#    #+#             */
/*   Updated: 2025/01/26 13:17:05 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	total = count * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}
/*
#include <stdio.h>
int main ()
{
	size_t num_elements = 5;
	size_t element_size = sizeof(int);
	int *array = (int *)calloc(num_elements, element_size);

	if (array == NULL)	
		return 1;

	printf("array[0] = %d\n", array[0]);
	printf("array[1] = %d\n", array[1]);
	printf("array[2] = %d\n", array[2]);
	printf("array[3] = %d\n", array[3]);
	printf("array[4] = %d\n", array[4]);
	free(array);
	return 0;
}*/
