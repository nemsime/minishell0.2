/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:30:15 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:30:16 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	exec_builtin_2(t_shell *sh, char **cmd, t_exec *cmds)
{
	if (!cmd)
		return (1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, cmds));
	else if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(sh, cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_free(cmd), ft_pwd(sh));
	else if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(sh, cmd, 1));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(sh, cmd));
	else if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(sh, cmd));
	else if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, sh), 1);
	return (restore_std(sh), ft_free(cmd), 1);
}

int	exec_builtin(t_shell *sh, char **cmd, t_exec *cmds, int state)
{
	if (state == 1)
	{
		if (handle_redirection(cmds) == -1)
			return (ft_free(cmd), restore_std(sh), 1);
		if (cmds->token)
		{
			ft_free(cmd);
			cmd = ft_split(cmds->cmd, ' ');
		}
	}
	return (exec_builtin_2(sh, cmd, cmds));
}
