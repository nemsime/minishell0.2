/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtumanya <mtumanya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:23 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 14:55:27 by mtumanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_count(char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
		i++;
	return (i);
}

static void	cd_set_oldpwd(t_shell *sh, t_cd *cd)
{
	cd->oldpwd = getcwd(NULL, 0);
	if (!cd->oldpwd)
	{
		cd->pwd_value = ft_strjoin("OLDPWD=", get_env_value("PWD", sh), 0);
		cd->export_dot[1] = cd->pwd_value;
		ft_export(sh, cd->export_dot, 0);
	}
	else
	{
		cd->export_dot[1] = ft_strjoin("OLDPWD=", cd->oldpwd, 0);
		ft_export(sh, cd->export_dot, 0);
		free(cd->oldpwd);
	}
}

static int	cd_go_to_path(t_shell *sh, t_cd *cd, char **cmd)
{
	if (cd->ccmd == 1)
	{
		cd->path = get_env_value("HOME", sh);
		if (!cd->path || cd->path[0] == '\0')
			return (ft_free(cmd), write(2, "bash: cd: HOME not set\n", 23),
				g_exit_status = 1, 1);
		if (chdir(cd->path) == -1)
			return (perror("cd"), ft_free(cmd), free(cd->path),
				g_exit_status = 1, 1);
		free(cd->path);
	}
	else if (cd->ccmd == 2 && !ft_strcmp(cmd[1], "~"))
	{
		if (chdir(sh->home) == -1)
			return (perror("cd"), ft_free(cmd), g_exit_status = 1, 1);
	}
	else if (chdir(cmd[1]) == -1)
	{
		cd->a = ft_strjoin("cd: ", cmd[1], 0);
		if (!cd->a)
			return (ft_free(cmd), g_exit_status = 1, 1);
		ft_free(cd->export_dot);
		return (perror(cd->a), free(cd->a), ft_free(cmd), g_exit_status = 1, 1);
	}
	return (0);
}

static void	cd_set_pwd(t_shell *sh, t_cd *cd, char **cmd)
{
	cd->oldpwd = getcwd(NULL, 0);
	if (!cd->oldpwd)
	{
		cd->pwd_value = ft_strjoin("PWD=", get_env_value("PWD", sh), 0);
		cd->tmp = cd->pwd_value;
		cd->pwd_value = ft_strjoin(cd->tmp, "/", 0);
		free(cd->tmp);
		cd->tmp = cd->pwd_value;
		cd->pwd_value = ft_strjoin(cd->pwd_value, cmd[1], 0);
		free(cd->tmp);
		cd->export_dot[1] = cd->pwd_value;
		ft_export(sh, cd->export_dot, 0);
		write(1, "cd: error retrieving current directory: ", 40);
		write(1, "getcwd: cannot access parent directories:\n", 42);
	}
	else
	{
		free(cd->export_dot[1]);
		cd->export_dot[1] = ft_strjoin("PWD=", cd->oldpwd, 0);
		ft_export(sh, cd->export_dot, 0);
		free(cd->oldpwd);
	}
}

int	ft_cd(t_shell *sh, char **cmd)
{
	t_cd	cd;

	cd.a = NULL;
	cd.ccmd = cmd_count(cmd);
	cd.export_dot = malloc(3 * sizeof(char *));
	cd.export_dot[0] = ft_strdup("export");
	cd.export_dot[1] = NULL;
	cd.export_dot[2] = NULL;
	if (cd.ccmd > 2)
		return (ft_free(cd.export_dot), ft_free(cmd),
			write(2, "bash: cd: too many arguments\n", 29),
			g_exit_status = 1, 1);
	cd_set_oldpwd(sh, &cd);
	if (cd_go_to_path(sh, &cd, cmd))
		return (1);
	cd_set_pwd(sh, &cd, cmd);
	if (g_exit_status == 1)
		return (ft_free(cmd), ft_free(cd.export_dot), 1);
	ft_free(cd.export_dot);
	return (ft_free(cmd), 0);
}
