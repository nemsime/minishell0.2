/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:53 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:54 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*get_env_value_from_list(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	find_path(t_env *env, char ***path)
{
	char	*path_value;

	path_value = get_env_value_from_list(env, "PATH");
	if (!path_value)
		return (0);
	*path = ft_split(path_value, ':');
	if (!*path)
		return (0);
	return (1);
}

char	*full_cmd(char **cmd)
{
	if (access(cmd[0], F_OK) != 0)
		return (ft_free_split(cmd), NULL);
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	return (ft_strdup(cmd[0]));
}

char	*find_cmd(char *command, t_env *env, int i, char *tmp)
{
	char	**paths;
	char	**cmd;

	if (find_path(env, &paths) == 0)
		return (NULL);
	cmd = ft_split(command, ' ');
	if (!cmd || !cmd[0])
		return (ft_free_split(paths), NULL);
	if (ft_strchr(cmd[0], '/'))
		return (ft_free_split(paths), full_cmd(cmd));
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/", 0);
		if (!tmp)
			return (ft_free_split(paths), ft_free_split(cmd), NULL);
		tmp = ft_strjoin(tmp, cmd[0], 1);
		if (!tmp)
			return (ft_free_split(paths), ft_free_split(cmd), NULL);
		if (access(tmp, X_OK) == 0)
			return (ft_free_split(paths), ft_free_split(cmd), tmp);
		free(tmp);
		i++;
	}
	return (ft_free_split(paths), ft_free_split(cmd), NULL);
}
