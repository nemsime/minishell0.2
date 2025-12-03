/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:34:15 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:34:16 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_input(char *file, t_exec *cmds)
{
	int		fd;
	char	*name;

	name = strip_quotes(file);
	fd = open(name, O_RDONLY);
	free(name);
	if (fd < 0)
	{
		print_error(file, "No such file or directory");
		g_exit_status = 1;
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), perror("dup2"), g_exit_status = 1, -1);
	close(fd);
	cmds->has_infile = 1;
	return (0);
}

int	redir_output(char *file, char *type, t_exec *cmds)
{
	int		fd;
	char	*name;

	name = strip_quotes(file);
	if (!ft_strncmp(type, ">>", 3))
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(name);
	if (fd < 0)
		return (perror(file), g_exit_status = 1, -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), perror("dup2"), g_exit_status = 1, -1);
	close(fd);
	cmds->has_outfile = 1;
	return (0);
}

static void	append_redir_extra(t_exec *cmds, char **tmp)
{
	int		k;
	char	*tmp2;

	k = 1;
	while (tmp[k])
	{
		if (!cmds->cmd)
			cmds->cmd = ft_strdup(tmp[k]);
		else
		{
			tmp2 = ft_strjoin(cmds->cmd, " \"", 1);
			cmds->cmd = ft_strjoin(tmp2, tmp[k], 1);
			cmds->cmd = ft_strjoin(cmds->cmd, "\"", 1);
		}
		k++;
	}
}

static int	apply_one_redir(t_exec *cmds, t_rsub *res)
{
	char	**tmp;
	int		ret;

	tmp = ft_split(res->arg, ' ');
	if (!tmp || !tmp[0])
		return (0);
	if (!ft_strncmp(res->op, "<", 1))
		ret = redir_input(tmp[0], cmds);
	else if (!ft_strncmp(res->op, ">", 1) || !ft_strncmp(res->op, ">>", 2))
		ret = redir_output(tmp[0], res->op, cmds);
	else
		ret = 0;
	append_redir_extra(cmds, tmp);
	ft_free(tmp);
	return (ret);
}

int	handle_redirection(t_exec *cmds)
{
	t_rsub	*sub_node;

	sub_node = cmds->subs;
	while (sub_node)
	{
		if (ft_strncmp(sub_node->op, "<<", 2) != 0)
		{
			if (apply_one_redir(cmds, sub_node) == -1)
				return (-1);
		}
		sub_node = sub_node->next;
	}
	return (0);
}
