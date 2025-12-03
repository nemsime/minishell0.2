/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:57 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:58 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes(char *s)
{
	char	*res;
	int		i;
	int		start;
	char	q;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			start = i;
			while (s[i] && s[i] != q)
				i++;
			res = ft_strjoin(res, ft_substr(s, start, i - start), 2);
			if (s[i])
				i++;
		}
		else
			res = ft_strjoin(res, ft_substr(s, i++, 1), 2);
	}
	return (res);
}

static void	droshak(int *drosh, char *arg)
{
	int	i;

	i = 0;
	*drosh = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			*drosh = 1;
			return ;
		}
		i++;
	}
}

void	herdoc_handle(t_shell *sh, t_exec **data, int count, int drosh)
{
	t_exec	*cur;
	t_rsub	*res;
	char	**tmp;

	cur = *data;
	while (cur)
	{
		res = cur->subs;
		while (res)
		{
			droshak(&drosh, res->arg);
			tmp = ft_split(res->arg, ' ');
			if (!ft_strncmp(res->op, "<<", 2))
				append_heredoc_extra(cur, tmp, sh, drosh);
			ft_free(tmp);
			res = res->next;
		}
		if (cur->cmd && cur->cmd[0] != '\0' && cur->cmd[0] != ' ')
			count++;
		cur = cur->next;
	}
	if (count > 0)
		sh->pipe_count = count - 1;
	else
		sh->pipe_count = 0;
}
