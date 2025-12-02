/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtumanya <mtumanya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:29:17 by szakarya          #+#    #+#             */
/*   Updated: 2025/12/01 19:43:16 by mtumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_shell *sh, char **cmd, int state)
{
	int	i;
	int	err;

	if (cmd_count(cmd) == 1)
	{
		ft_print_export(sh);
		if (state == 1)
			ft_free(cmd);
		return (g_exit_status = 0, 0);
	}
	err = 0;
	i = 1;
	while (cmd[i])
	{
		if (export_one(sh, cmd[i], NULL))
			err = 1;
		i++;
	}
	g_exit_status = err;
	if (state == 1)
		ft_free(cmd);
	return (err);
}
