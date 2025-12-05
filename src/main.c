/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:34:02 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:34:03 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main_loop_help(t_shell *shell, char *expanded)
{
	expanded = expand_vars(shell->input, shell, 1);
	free(shell->input);
	shell->input = expanded;
	g_exit_status = 0;
	if (token(shell, 0, 0))
	{
		free(shell->input);
		return (1);
	}
	if (!shell->tokens || !shell->tokens[0])
	{
		free(shell->input);
		return (1);
	}
	if (shell->pipe_count > 1024)
	{
		g_exit_status = 1;
		free(shell->input);
		ft_free(shell->tokens);
		printf("Error: Too many pipes\n");
		return (1);
	}
	return (0);
}

void	main_loop(t_shell *shell, char *expanded)
{
	while (1)
	{
		init_shell(shell);
		shell->input = readline("\001\033[1;34m\002MiniShell $ "
				"\001\033[1;36m\002");
		if (!shell->input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			free(shell->input);
			break ;
		}
		if (*shell->input == '\0')
		{
			free(shell->input);
			continue ;
		}
		add_history(shell->input);
		if (main_loop_help(shell, expanded))
			continue ;
		if (start(shell, 0) == -1)
			break ;
		reinit(&shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	g_exit_status = 0;
	if (argc != 1)
	{
		write(2, "\033[1;31mNo arguments needed\n", 28);
		return (1);
	}
	init_shell(&shell);
	init_env(&shell, envp);
	shell.home = get_env_value("HOME", &shell);
	if (!shell.t_env)
	{
		write(2, "\033[1;31mEnv init Error\n", 23);
		return (1);
	}
	set_signals();
	main_loop(&shell, NULL);
	rl_clear_history();
	free_env(shell.t_env);
	free(shell.home);
	return (g_exit_status);
}
