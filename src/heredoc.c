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

char	*strip_quotes(char *s, char *res)
{
	int		i;
	int		start;
	char	q;

	if (!s)
		return (res);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			start = i;
			while (s[i] && s[i] != q)
				i++;
			res = ft_strjoin(res, ft_substr(s, start, i - start), 2);
			if (s[i])
				i++;
		}
		else
			res = ft_strjoin(res, ft_substr(s, i++, 1), 2);
	}
	return (res);
}

static void	write_heredoc_input(int fd,
	char *delimiter, t_shell *sh, char *line)
{
	char	*expanded;

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
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
		expanded = expand_vars(line, sh, 0);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(line);
		free(expanded);
	}
	set_signals();
}

static void	collect_one_heredoc(t_exec *owner, char *delim, t_shell *sh)
{
	int		p[2];
	char	*clean;

	if (pipe(p) == -1)
		ft_exit_perror("pipe");
	clean = strip_quotes(delim, ft_strdup(""));
	write_heredoc_input(p[1], clean, sh, NULL);
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

static void	append_heredoc_extra(t_exec *cur, char **tmp, t_shell *sh)
{
	int		k;
	char	*tmp2;

	k = 1;
	collect_one_heredoc(cur, tmp[0], sh);
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

void	herdoc_handle(t_shell *sh, t_exec **data, int count)
{
	t_exec	*cur;
	t_rsub	*res;
	char	**tmp;

	cur = *data;
	while (cur)
	{
		res = cur->subs;
		while (res)
		{
			tmp = ft_split(res->arg, ' ');
			if (!ft_strncmp(res->op, "<<", 2))
				append_heredoc_extra(cur, tmp, sh);
			ft_free(tmp);
			res = res->next;
		}
		if (cur->cmd && cur->cmd[0] != '\0' && cur->cmd[0] != ' ')
			count++;
		cur = cur->next;
	}
	if (count > 0)
		sh->pipe_count = count - 1;
	else
		sh->pipe_count = 0;
}
