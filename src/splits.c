/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:38 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:42:57 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_sub(t_exec *cur, char *op, char *arg)
{
	t_rsub	*it;

	if (!cur || !op || !arg)
		return (0);
	if (!cur->subs)
	{
		cur->subs = new_sub(op, arg);
		return (!!cur->subs);
	}
	it = cur->subs;
	while (it->next)
		it = it->next;
	it->next = new_sub(op, arg);
	return (!!it->next);
}

static void	append_word(t_exec *cur, char *w)
{
	char	*tmp;

	if (!w || !*w)
		return ;
	if (!cur->cmd)
	{
		cur->cmd = ft_strdup(w);
		return ;
	}
	tmp = ft_strjoin(cur->cmd, " ", 1);
	cur->cmd = ft_strjoin(tmp, w, 1);
}

void	split_by_pipe_2(t_shell *sh, int *i, t_exec *cur)
{
	append_sub(cur, sh->tokens[*i], sh->tokens[*i + 1]);
	cur->token = sh->tokens[*i];
	cur->cmd2 = ft_strdup(sh->tokens[*i + 1]);
	*i += 2;
}

static void	helper(t_shell *sh, int *i, t_exec *cur)
{
	split_by_pipe_2(sh, i, cur);
	if (cur->cmd2)
	{
		free(cur->cmd2);
		cur->cmd2 = NULL;
	}
}

t_exec	*split_by_pipe(t_shell *sh, int i, t_exec *head, t_exec *cur)
{
	if (!head)
		return (NULL);
	cur = head;
	while (sh->tokens[i])
	{
		if (is_pipe_tok(sh->tokens[i]))
		{
			cur->next = new_exec_node();
			cur = cur->next;
			i++;
			continue ;
		}
		if (is_redir_tok(sh->tokens[i]))
		{
			if (sh->tokens[i + 1])
			{
				helper(sh, &i, cur);
				continue ;
			}
		}
		if (ft_strncmp(sh->tokens[i], " ", 2) != 0)
			append_word(cur, sh->tokens[i]);
		i++;
	}
	return (head);
}
