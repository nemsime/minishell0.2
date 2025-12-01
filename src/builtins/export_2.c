/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szakarya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:29:17 by szakarya          #+#    #+#             */
/*   Updated: 2025/11/04 02:28:53 by szakarya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	valid_export_key(char *s)
{
	int	i;

	if (!s || (!ft_isalpha((unsigned char)s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (2);
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
 
static void	export_new_value(t_shell *sh, char *key, char *val)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (free(key), free(val));
	new->key = key;
	new->value = val;
	new->next = NULL;
	tmp = sh->t_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	export_one_2(char *arg, char *eq, char **key, char **val)
{
	int type = valid_export_key(arg);
	if (!type)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (eq)
	{
		if(type == 2)
			*key = ft_substr(arg, 0, (size_t)(eq - arg - 1));
		else
			*key = ft_substr(arg, 0, (size_t)(eq - arg));
		*val = ft_strdup(eq + 1);
	}
	else
		*key = ft_strdup(arg);
	if (!(*key) || (eq && !(*val)))
		return (free(*key), free(*val), 1);
	if(type == 2)
		return (2);
	return (0); 
}

static int	export_one(t_shell *sh, char *arg, char *val)
{
	char	*eq;
	char	*key;
	t_env	*n;
	
	eq = ft_strchr(arg, '=');

	int type = export_one_2(arg, eq, &key, &val);
	if (type == 1)
		return (1);
	n = sh->t_env;
	while (n)
	{
		if (!ft_strcmp(n->key, key))
		{
			if (eq)
			{
				if (type == 2) 
				{
					char *newv = ft_strjoin(n->value, val,0);
					free(n->value);
					n->value = newv;
					free(val);
				}
				else
				{
					free(n->value);
					n->value = val;
				}
			}
			else
				free(val);
			return (free(key), 0);
		}
		n = n->next;
	}
	export_new_value(sh, key, val);
	return (0);
}

int	ft_export(t_shell *sh, char **cmd, int state)
{
	int	i;
	int	err;

	if (cmd_count(cmd) == 1)
	{
		ft_print_export(sh);
		if (state == 1)
			ft_free(cmd);
		return (g_exit_status = 0, 0);
	}
	err = 0;
	i = 1;
	while (cmd[i])
	{
		if (export_one(sh, cmd[i], NULL))
			err = 1;
		i++;
	}
	g_exit_status = err;
	if (state == 1)
		ft_free(cmd);
	return (err);
}
