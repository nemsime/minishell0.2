/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:17:26 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:32:29 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(const char *s, char c, int i, size_t count)
{
	char	quote;

	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;
		}
		else
		{
			while (s[i] && s[i] != c && s[i] != '\'' && s[i] != '"')
				i++;
		}
	}
	return (count);
}

static char	*extract_token(const char **s, char c)
{
	char	*buf;
	int		i;
	char	quote;

	i = 0;
	buf = malloc(ft_strlen(*s) + 1);
	if (!buf)
		return (NULL);
	while (**s && **s != c)
	{
		if (**s == '\'' || **s == '"')
		{
			quote = *(*s)++;
			while (**s && **s != quote)
				buf[i++] = *(*s)++;
			if (**s == quote)
				(*s)++;
		}
		else
			buf[i++] = *(*s)++;
	}
	buf[i] = '\0';
	return (buf);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = word_count(s, c, 0, 0);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[i] = extract_token((const char **)&s, c);
			if (!res[i])
				return (NULL);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
