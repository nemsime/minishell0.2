/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:29:57 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:29:58 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_input_help(int fd,
	char *expanded, char *line)
{
	write(fd, "\n", 1);
	free(line);
	free(expanded);
}

static void	write_heredoc_input(int fd,
	char *delimiter, t_shell *sh, int drosh)
{
	char	*expanded;
	char	*line;

	line = NULL;
	while (1 && g_exit_status != 130)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (g_exit_status == 130)
		{
			free(line);
			break ;
		}
		if (drosh)
			expanded = ft_strdup(line);
		else
			expanded = expand_vars(line, sh, 0);
		write(fd, expanded, ft_strlen(expanded));
		write_heredoc_input_help(fd, expanded, line);
	}
}

static void	collect_one_heredoc(t_exec *owner,
	char *delim, t_shell *sh, int drosh)
{
	int		p[2];
	char	*clean;

	if (pipe(p) == -1)
		ft_exit_perror("pipe");
	clean = strip_quotes(delim);
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	write_heredoc_input(p[1], clean, sh, drosh);
	set_signals();
	free(clean);
	close(p[1]);
	if (g_exit_status == 130)
	{
		close(p[0]);
		owner->heredoc_fd = -1;
		return ;
	}
	if (owner->heredoc_fd > 0)
		close(owner->heredoc_fd);
	owner->heredoc_fd = p[0];
}

void	append_heredoc_extra(t_exec *cur,
	char **tmp, t_shell *sh, int drosh)
{
	int		k;
	char	*tmp2;

	k = 1;
	collect_one_heredoc(cur, tmp[0], sh, drosh);
	while (tmp[k])
	{
		if (!cur->cmd)
			cur->cmd = ft_strdup(tmp[k]);
		else
		{
			tmp2 = ft_strjoin(cur->cmd, " ", 1);
			cur->cmd = ft_strjoin(tmp2, tmp[k], 1);
		}
		k++;
	}
}
