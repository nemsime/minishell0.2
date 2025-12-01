/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:30:02 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:31 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atol(const char *str, int *state)
{
	unsigned long long	result;
	int					sign;
	int					i;

	i = 0;
	sign = 1;
	result = 0;
	*state = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if ((sign == -1 && result > 9223372036854775808ULL)
		|| (sign == 1 && result > 9223372036854775807ULL))
		return (*state = 1);
	return (sign * result);
}

void	ft_exit_loop(char **argv, int state)
{
	int		i;

	i = 0;
	while (argv[1][i])
	{
		if (i == 0 && (argv[1][i] == '-' || argv[1][i] == '+'))
			i++;
		if (!ft_isdigit(argv[1][i]) || state == 1)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			ft_free(argv);
			exit(2);
		}
		i++;
	}
}

int	isnumeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (!arg[i] && ft_isdigit(arg[i - 1]))
		return (1);
	return (0);
}

static void	free_for_exit(char **argv, t_shell *shell)
{
	free(shell->input);
	ft_free(shell->tokens);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	ft_free(argv);
}

int	ft_exit(char **argv, t_shell *shell)
{
	int		status;
	long	num;
	int		state;

	status = g_exit_status;
	if (shell->pipe_count == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argv[0] && argv[1])
	{
		num = ft_atol(argv[1], &state);
		if (argv[2] && isnumeric(argv[1]) && state == 0)
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return (ft_free(argv), g_exit_status = 1, 1);
		}
		ft_exit_loop(argv, state);
		status = (int)(num % 256);
		if (status < 0)
			status += 256;
	}
	free_for_exit(argv, shell);
	exit(status);
}
