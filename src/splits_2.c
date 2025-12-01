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
