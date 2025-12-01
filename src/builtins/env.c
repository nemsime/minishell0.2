/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:27 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:28 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_shell *sh, char **cmd)
{
	t_env	*tmp;

	tmp = sh->t_env;
	if (cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd[1]);
		return (ft_free(cmd), g_exit_status = 127, 1);
	}
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (ft_free(cmd), 0);
}
