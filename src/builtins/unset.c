/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:39 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:40 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_env(t_shell *sh, char **cmd, int count)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = sh->t_env;
	prev = NULL;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->key, cmd[count]))
		{
			if (prev == NULL)
				sh->t_env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_shell *sh, char **cmd)
{
	int	count;

	if (!sh->t_env)
		return (0);
	count = cmd_count(cmd);
	while (count-- != 1)
	{
		unset_env(sh, cmd, count);
	}
	ft_free(cmd);
	return (0);
}
