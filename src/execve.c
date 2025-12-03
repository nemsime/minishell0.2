/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:45 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:46 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipes_and_redir(t_exec *cmds, t_vars *vars, int i, t_shell *sh)
{
	int	j;

	if (handle_redirection(cmds) == -1)
		exit(g_exit_status);
	if (i > 0 && !cmds->has_infile && dup2(vars->pfd[i - 1][0],
		STDIN_FILENO) < 0)
		ft_exit_perror("dup2 stdin");
	if (i < sh->pipe_count && !cmds->has_outfile && dup2(vars->pfd[i][1],
		STDOUT_FILENO) < 0)
		ft_exit_perror("dup2 stdout");
	if (cmds->heredoc_fd > 0)
	{
		dup2(cmds->heredoc_fd, STDIN_FILENO);
		close(cmds->heredoc_fd);
	}
	j = -1;
	while (++j < sh->pipe_count)
	{
		close(vars->pfd[j][0]);
		close(vars->pfd[j][1]);
	}
}

static void	handle_special_cmds(t_exec *cmds, t_shell *sh, char *tmp)
{
	if (ft_strncmp(tmp, ".", 2) == 0)
	{
		ft_putstr_fd("shell: .: filename argument required\n", STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		restore_std(sh);
		free(tmp);
		ft_free_execs(cmds);
		exit(2);
	}
	if (ft_strncmp(tmp, "..", 3) == 0)
	{
		restore_std(sh);
		print_error(tmp, "command not found");
		free(tmp);
		ft_free_execs(cmds);
		exit(127);
	}
	if (ft_strncmp(tmp, "\"\"", 3) == 0)
	{
		restore_std(sh);
		print_error("''", "command not found");
		free(tmp);
		ft_free_execs(cmds);
		exit(127);
	}
}

static void	handle_builtin_or_path(t_exec *cmds, t_vars *vars, t_shell *sh)
{
	vars->cmd = ft_split(cmds->cmd, ' ');
	if (cmds && is_builtin(vars->cmd[0]))
	{
		g_exit_status = exec_builtin(sh, vars->cmd, cmds, 0);
		ft_free_execs(cmds);
		exit(g_exit_status);
	}
	vars->path = find_cmd(cmds->cmd, sh->t_env, -1, NULL);
	if (!vars->path)
	{
		restore_std(sh);
		if (ft_strchr(vars->cmd[0], '/'))
		{
			print_error(vars->cmd[0], "No such file or directory");
			ft_free(vars->cmd);
			exit(127);
		}
		else
		{
			print_error(vars->cmd[0], "command not found");
			ft_free(vars->cmd);
			exit(127);
		}
	}
}

static int	check_directory_and_exec(t_exec *cmds, t_vars *vars, t_shell *sh,
		char **env_arr)
{
	struct stat	st;

	if (stat(vars->path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		restore_std(sh);
		print_error(cmds->cmd, "Is a directory");
		free(vars->path);
		exit(126);
	}
	errno = 0;
	execve(vars->path, vars->cmd, env_arr);
	restore_std(sh);
	if (errno == ENOENT)
		print_error(cmds->cmd, "No such file or directory");
	else if (errno == EACCES)
		print_error(cmds->cmd, "Permission denied");
	else if (errno == ENOEXEC)
		print_error(cmds->cmd, "Exec format error");
	else
		ft_exit_perror("shell");
	return (errno);
}

void	redirections_execve(t_exec *cmds, t_vars *vars, int i, t_shell *sh)
{
	int		status;
	char	**env_arr;
	char	*tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pipes_and_redir(cmds, vars, i, sh);
	if (ft_strncmp(cmds->cmd, " ", 2) == 0 && (cmds->token
			&& ft_strncmp(cmds->token, "<<", 3) == 0))
		exit(0);
	tmp = strip_quotes(cmds->cmd);
	handle_special_cmds(cmds, sh, tmp);
	free(tmp);
	handle_builtin_or_path(cmds, vars, sh);
	env_arr = env_list_to_array(sh->t_env, 0);
	status = check_directory_and_exec(cmds, vars, sh, env_arr);
	free(vars->path);
	ft_free(vars->cmd);
	ft_free(env_arr);
	if (status == ENOENT)
		exit(127);
	exit(126);
}
