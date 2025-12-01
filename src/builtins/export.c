/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:33:34 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:33:35 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_nodes(t_env *node)
{
	int	count;

	count = 0;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

static void	print_one_export(t_env *e)
{
	if (e->value)
		printf("declare -x %s=\"%s\"\n", e->key, e->value);
	else
		printf("declare -x %s\n", e->key);
}

static void	fill_env_array(t_env **arr, t_env *node)
{
	int	i;

	i = 0;
	while (node)
	{
		arr[i++] = node;
		node = node->next;
	}
}

static void	sort_env_array(t_env **arr, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_export(t_shell *sh)
{
	int		count;
	int		i;
	t_env	**arr;

	count = count_env_nodes(sh->t_env);
	if (count == 0)
		return ;
	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return ;
	fill_env_array(arr, sh->t_env);
	sort_env_array(arr, count);
	i = 0;
	while (i < count)
		print_one_export(arr[i++]);
	free(arr);
}
