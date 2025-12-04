/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:34:19 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:34:20 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*new_exec_node(void)
{
	t_exec	*n;

	n = malloc(sizeof(t_exec));
	if (!n)
		return (NULL);
	n->cmd = NULL;
	n->cmd2 = NULL;
	n->token = NULL;
	n->heredoc_fd = -1;
	n->has_infile = 0;
	n->has_outfile = 0;
	n->next = NULL;
	n->subs = NULL;
	return (n);
}

int	is_pipe_tok(char *s)
{
	if (!s)
		return (0);
	return (!ft_strncmp(s, "|", 1));
}

int	is_redir_tok(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (1);
	if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">", 1))
		return (1);
	return (0);
}

t_rsub	*new_sub(char *op, char *arg)
{
	t_rsub	*r;

	r = malloc(sizeof(t_rsub));
	if (!r)
		return (NULL);
	r->op = ft_strdup(op);
	r->arg = ft_strdup(arg);
	r->next = NULL;
	return (r);
}

int	extract_cmd_from_cmd2(t_exec *cur, int i)
{
	char	**sp;

	if (cur->cmd || !cur->cmd2
		|| (cur->token && ft_strncmp(cur->token, "<<", 2) == 0))
		return (1);
	sp = ft_split(cur->cmd2, ' ');
	if (!sp || !sp[0] || !sp[1])
		return (ft_free(sp), 1);
	if (sp[1])
		cur->cmd = ft_strdup(sp[1]);
	if (sp[2] && sp[2][0] == '-')
	{
		cur->cmd = ft_strjoin(cur->cmd, " ", 1);
		cur->cmd = ft_strjoin(cur->cmd, sp[2], 1);
		i = 3;
	}
	free(cur->subs->arg);
	cur->subs->arg = ft_strdup(sp[0]);
	while (sp[i])
	{
		cur->subs->arg = ft_strjoin(cur->cmd, " ", 1);
		cur->subs->arg = ft_strjoin(cur->cmd, sp[i], 1);
		i++;
	}
	return (ft_free(sp), 1);
}
