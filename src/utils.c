/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:56 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:57 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_shell *sh)
{
	if (dup2(sh->stdin_backup, STDIN_FILENO) == -1)
		ft_exit_perror("dup2 restore stdin");
	if (dup2(sh->stdout_backup, STDOUT_FILENO) == -1)
		ft_exit_perror("dup2 restore stdout");
}

void	print_error(const char *arg, const char *msg)
{
	ft_putstr_fd("shell: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	is_operator(const char *s, int *len, t_data *type)
{
	if (!s || !*s)
		return (0);
	if (s[0] == '<' && s[1] == '<' && s[2] == '<')
		return (*len = 3, *type = T_REDIR_IN, 1);
	if (s[0] == '|' && s[1] == '|')
		return (*len = 2, *type = PIPE, 1);
	if (s[0] == '>' && s[1] == '>')
		return (*len = 2, *type = APPEND, 1);
	if (s[0] == '<' && s[1] == '<')
		return (*len = 2, *type = HEREDOC, 1);
	if (s[0] == '|')
		return (*len = 1, *type = PIPE, 1);
	if (s[0] == '<')
		return (*len = 1, *type = REDIR_IN, 1);
	if (s[0] == '>')
		return (*len = 1, *type = REDIR_OUT, 1);
	return (0);
}

char	*ft_join(char *a, char *b, char *c)
{
	char	*res;

	if (a == NULL)
		res = ft_strjoin("shell: ", b, 0);
	else
	{
		res = ft_strjoin(a, ": ", 0);
		res = ft_strjoin(res, b, 1);
	}
	res = ft_strjoin(res, c, 1);
	return (res);
}

char	**env_list_to_array(t_env *env, int count)
{
	int		i;
	char	**arr;
	char	*joined;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->key && env->value)
		{
			joined = ft_strjoin(env->key, "=", 0);
			arr[i++] = ft_strjoin(joined, env->value, 1);
		}
		env = env->next;
	}
	return (arr[i] = NULL, arr);
}
