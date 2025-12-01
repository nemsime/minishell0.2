/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:56 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:57 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arg)
{
	int	i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	ft_exit_perror(const char *msg)
{
	if (errno == EPIPE)
		exit(1);
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_free_execs(t_exec *cmds)
{
	t_exec	*tmp;
	t_rsub	*n;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->heredoc_fd > 0)
			close(cmds->heredoc_fd);
		if (cmds->cmd)
			free(cmds->cmd);
		if (cmds->cmd2)
			free(cmds->cmd2);
		while (cmds->subs)
		{
			n = cmds->subs->next;
			free(cmds->subs->op);
			free(cmds->subs->arg);
			free(cmds->subs);
			cmds->subs = n;
		}
		free(cmds);
		cmds = tmp;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*current;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		tmp = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = tmp;
	}
	env = NULL;
}
