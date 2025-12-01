/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtumanya <mtumanya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:59 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 14:49:54 by mtumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_dollar_2(t_exp *e, size_t len, char **val)
{
	if (*val)
		len = ft_strlen(*val);
	if (!buf_grow(e, len))
		return (free(*val), -1);
	ft_memcpy(e->out + e->j, *val, len);
	e->j += len;
	free(*val);
	return (0);
}

static int	handle_dollar(t_exp *e, size_t len)
{
	size_t	is_q;
	size_t	nlen;
	char	*name;
	char	*val;

	nlen = parse_var_name(e->in + e->i + 1, &is_q);
	if (nlen == 0)
		return (0);
	if (is_q)
		val = ft_itoa(g_exit_status);
	else if (e->in[e->i + 1] == '$')
		val = ft_itoa(getpid());
	else
	{
		name = ft_substr(e->in, e->i + 1, nlen);
		val = get_env_value(name, e->sh);
		free(name);
	}
	if (handle_dollar_2(e, len, &val) == -1)
		return (-1);
	if (is_q)
		e->i += 2;
	else
		e->i += 1 + nlen;
	return (1);
}

static int	helper_expend_loop(t_exp e, int cas)
{
	if (!e.sq && !e.dq && e.in[e.i] == '<' && cas == 1
		&& e.in[e.i + 1] != '\0' && e.in[e.i + 1] == '<')
	{
		if (!copy_heredoc(&e, 0))
			return (free(e.out), 1);
		return (2);
	}
	return (0);
}

char	*expand_loop(t_exp e, int r, int cas, int help)
{
	while (e.in[e.i])
	{
		help = helper_expend_loop(e, cas);
		if (help == 1)
			return (NULL);
		if (help == 2)
			continue ;
		r = handle_quote(&e);
		if (r == 0)
			return (free(e.out), NULL);
		if (r == 1)
			continue ;
		if (!e.sq && e.in[e.i] == '$')
		{
			r = handle_dollar(&e, 0);
			if (r == -1)
				return (free(e.out), NULL);
			if (r == 1)
				continue ;
		}
		if (!buf_grow(&e, 1))
			return (free(e.out), NULL);
		e.out[e.j++] = e.in[e.i++];
	}
	return (e.out[e.j] = '\0', e.out);
}

char	*expand_vars(char *input, t_shell *shell, int cas)
{
	t_exp	e;

	if (!input || !shell)
		return (ft_strdup(""));
	e = (t_exp){.in = input, .sh = shell, .i = 0, .j = 0,
		.sq = 0, .dq = 0, .cap = ft_strlen(input) * 2 + 1};
	e.out = ft_calloc(1, e.cap);
	if (!e.out)
		return (NULL);
	return (expand_loop(e, 0, cas, 0));
}
