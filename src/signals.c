/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:30:01 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:30:02 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handling_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
}

void	sigint_during_wait(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	set_signals(void)
{
	signal(SIGINT, &handling_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_heredoc(int sig)
{
	g_exit_status = 130;
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	return ;
}
