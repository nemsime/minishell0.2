/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:52 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:53 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_tokens_help(const char *s, int *i, char q)
{
	if (s[*i] == '"' || s[*i] == '\'')
	{
		q = s[(*i)++];
		while (s[*i] && s[*i] != q)
			(*i)++;
		if (s[*i] == q)
			(*i)++;
	}
	else
		(*i)++;
}

static int	count_tokens(const char *s, int i)
{
	int		len;
	t_data	type;
	int		count;

	count = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break ;
		if (is_operator(&s[i], &len, &type))
		{
			count++;
			i += len;
		}
		else
		{
			while (s[i] && !is_operator(&s[i], &len, &type))
				count_tokens_help(s, &i, 0);
			count++;
		}
	}
	return (count);
}

static char	*extract_token(const char *s, int *i, int start, int end)
{
	char	quote;
	int		len;
	t_data	type;

	if (is_operator(&s[*i], &len, &type))
		return (*i += len, ft_substr(s, start, len));
	while (s[*i] && !is_operator(&s[*i], &len, &type))
	{
		if (s[*i] == '"' || s[*i] == '\'')
		{
			quote = s[(*i)++];
			while (s[*i] && s[*i] != quote)
				(*i)++;
			if (s[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	end = *i;
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	return (ft_substr(s, start, end - start));
}

static int	token_loop(t_shell *sh, int i, int j)
{
	while (sh->input[i])
	{
		while (sh->input[i] == ' ' || sh->input[i] == '\t')
			i++;
		if (!sh->input[i])
			break ;
		sh->tokens[j] = extract_token(sh->input, &i, i, 0);
		if (!sh->tokens[j])
			return (ft_free(sh->tokens), 1);
		if (!ft_strncmp(sh->tokens[j], "|", 1))
			sh->pipe_count++;
		if (!ft_strncmp(sh->tokens[j], "<<", 2))
			sh->heredocs++;
		j++;
	}
	sh->tokens[j] = NULL;
	return (0);
}

int	token(t_shell *sh, int i, int j)
{
	if (has_open_quote(sh->input))
		return (1);
	sh->tok_count = count_tokens(sh->input, 0);
	if (sh->tok_count == 0)
		return (1);
	sh->tokens = malloc(sizeof(char *) * (sh->tok_count + 1));
	if (!sh->tokens)
		return (1);
	if (token_loop(sh, i, j))
		return (1);
	if (syntax_error(sh, 0))
	{
		g_exit_status = 2;
		ft_free(sh->tokens);
		return (1);
	}
	if (sh->pipe_count > 1024)
	{
		g_exit_status = 1;
		ft_free(sh->tokens);
		return (1);
	}
	return (0);
}
