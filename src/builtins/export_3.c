/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtumanya <mtumanya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:29:17 by szakarya          #+#    #+#             */
/*   Updated: 2025/12/01 19:43:16 by mtumanya         ###   ########.fr       */
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
	int	type;

	type = valid_export_key(arg);
	if (!type)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (eq)
	{
		if (type == 2)
			*key = ft_substr(arg, 0, (size_t)(eq - arg - 1));
		else
			*key = ft_substr(arg, 0, (size_t)(eq - arg));
		*val = ft_strdup(eq + 1);
	}
	else
		*key = ft_strdup(arg);
	if (!(*key) || (eq && !(*val)))
		return (free(*key), free(*val), 1);
	if (type == 2)
		return (2);
	return (0);
}

static void	update_env_value(int type, t_env **n, char *val)
{
	char	*newv;

	if (type == 2)
	{
		newv = ft_strjoin((*n)->value, val, 0);
		free((*n)->value);
		(*n)->value = newv;
		free(val);
	}
	else
	{
		free((*n)->value);
		(*n)->value = val;
	}
}

int	export_one(t_shell *sh, char *arg, char *val)
{
	char	*eq;
	char	*key;
	t_env	*n;
	int		type;

	eq = ft_strchr(arg, '=');
	type = export_one_2(arg, eq, &key, &val);
	if (type == 1)
		return (1);
	n = sh->t_env;
	while (n)
	{
		if (!ft_strcmp(n->key, key))
		{
			if (eq)
				update_env_value(type, &n, val);
			else
				free(val);
			return (free(key), 0);
		}
		n = n->next;
	}
	export_new_value(sh, key, val);
	return (0);
}
