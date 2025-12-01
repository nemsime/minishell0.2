/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:54 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:55 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, t_shell *shell)
{
	t_env	*env;
	size_t	len;

	if (!name || !shell || !shell->t_env)
		return (ft_strdup(""));
	if (name[0] == '?' && name[1] == '\0')
		return (ft_itoa(g_exit_status));
	len = ft_strlen(name);
	env = shell->t_env;
	while (env)
	{
		if (ft_strncmp(env->key, name, len) == 0
			&& env->key[len] == '\0' && (env->value != NULL))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

size_t	parse_var_name(const char *s, size_t *is_qmark)
{
	size_t	i;

	i = 0;
	*is_qmark = 0;
	if (s[i] == '$')
		return (1);
	if (s[i] == '?')
	{
		*is_qmark = 1;
		return (1);
	}
	if (!(ft_isalpha((unsigned char)s[i]) || s[i] == '_'))
		return (0);
	i++;
	while (s[i] && (ft_isalnum((unsigned char)s[i]) || s[i] == '_'))
		i++;
	return (i);
}

int	buf_grow(t_exp *e, size_t extra)
{
	size_t	need;
	size_t	newcap;
	char	*newbuf;

	need = e->j + extra + 1;
	if (need <= e->cap)
		return (1);
	newcap = e->cap * 2;
	if (newcap < need)
		newcap = need;
	newbuf = ft_calloc(1, newcap);
	if (!newbuf)
		return (0);
	if (e->out && e->j)
		ft_memcpy(newbuf, e->out, e->j);
	free(e->out);
	e->out = newbuf;
	e->cap = newcap;
	return (1);
}

int	copy_heredoc(t_exp *e, char q)
{
	size_t	start;

	start = e->i;
	e->i += 2;
	while (e->in[e->i] == ' ' || e->in[e->i] == '\t')
		e->i++;
	while (e->in[e->i] && e->in[e->i] != ' ' && e->in[e->i] != '\t')
	{
		if (e->in[e->i] == '\'' || e->in[e->i] == '"')
		{
			q = e->in[e->i++];
			while (e->in[e->i] && e->in[e->i] != q)
				e->i++;
			if (e->in[e->i] == q)
				e->i++;
		}
		else
			e->i++;
	}
	if (!buf_grow(e, e->i - start))
		return (0);
	ft_memcpy(e->out + e->j, e->in + start, e->i - start);
	e->j += (e->i - start);
	return (1);
}

int	handle_quote(t_exp *e)
{
	if (!e->dq && e->in[e->i] == '\'')
	{
		if (!buf_grow(e, 1))
			return (0);
		e->sq = !e->sq;
		e->out[e->j++] = e->in[e->i++];
		return (1);
	}
	if (!e->sq && e->in[e->i] == '"')
	{
		if (!buf_grow(e, 1))
			return (0);
		e->dq = !e->dq;
		e->out[e->j++] = e->in[e->i++];
		return (1);
	}
	return (2);
}
