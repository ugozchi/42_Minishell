/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:35 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 15:39:57 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_value(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_cpy_env(char *type, char *value, t_env **env, t_data *data)
{
	t_env	*node;
	t_env	*new_last_node;

	new_last_node = (t_env *)malloc(sizeof(t_env));
	if (!new_last_node)
		return ;
	new_last_node->type = type;
	new_last_node->equal = '=';
	new_last_node->value = value;
	new_last_node->next = NULL;
	if (!*env)
	{
		*env = new_last_node;
		if (data != NULL)
			data->cpy_env = *env;
	}
	else
	{
		node = last_value(*env);
		node->next = new_last_node;
	}
	return ;
}

void	get_shlvl_env(t_data *data)
{
	t_env	*env;
	int		lvl;
	int		i;

	i = 0;
	env = data->cpy_env;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "SHLVL=", 6))
			lvl = ft_atoll(data->env[i] + 6);
		i++;
	}
	while (env)
	{
		if (!ft_strcmp(env->type, "SHLVL"))
		{
			free(env->value);
			env->value = ft_itoa(lvl + 1);
		}
		env = env->next;
	}
	return ;
}

void	ft_get_env(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*cpy_env;

	cpy_env = NULL;
	data->env = env;
	if (!env[0] || !env)
	{
		add_cpy_env(ft_strdup("PWD"), getcwd(NULL, 0), &cpy_env, data);
		add_cpy_env(ft_strdup("SHLVL"), ft_strdup("1"), &cpy_env, data);
		add_cpy_env(ft_strdup("_"), ft_strdup("/usr/bin/env"),
			&cpy_env, data);
		return ;
	}
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		add_cpy_env(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
				ft_strlen(env[i])), &cpy_env, data);
		i++;
	}
	get_shlvl_env(data);
}
