/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:29:17 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:07 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_both(char *ptr, char *tmp_s1, char *tmp_s2, int should_free)
{
	if (should_free > 0 && ptr[0] != '\0')
		free(tmp_s1);
	if (should_free > 1 && ptr[0] != '\0' && tmp_s2)
		free(tmp_s2);
}

char	*ft_strjoin(char *s1, char *s2, int should_free)
{
	unsigned int	i;
	int				tmp;
	char			*ptr;
	char			*tmp_s1;
	char			*tmp_s2;

	if (!s1)
		return (0);
	tmp_s1 = s1;
	tmp_s2 = s2;
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	tmp = ft_strlen(s1);
	while (tmp-- != 0)
		ptr[i++] = *s1++;
	tmp = ft_strlen(s2);
	while (tmp-- != 0)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	free_both(ptr, tmp_s1, tmp_s2, should_free);
	return (ptr);
}
