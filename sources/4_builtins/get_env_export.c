/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:37 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:59:38 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_export(char *type, char *value, t_env **env, t_data *data)
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
			data->export = *env;
	}
	else
	{
		node = last_value(*env);
		node->next = new_last_node;
	}
	return ;
}

void	get_shlvl_export(t_data *data)
{
	t_env	*export;
	int		lvl;
	int		i;

	i = 0;
	export = data->export;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "SHLVL=", 6))
			lvl = ft_atoll(data->env[i] + 6);
		i++;
	}
	while (export)
	{
		if (!ft_strcmp(export->type, "SHLVL"))
		{
			free(export->value);
			export->value = ft_itoa(lvl + 1);
		}
		export = export->next;
	}
	return ;
}

static void	export_without_env(t_data *data, t_env *export)
{
	if (!*data->env)
	{
		add_export(ft_strdup("OLDPWD"), ft_strdup(""), &export, data);
		add_export(ft_strdup("PWD"), getcwd(NULL, 0), &export, data);
		add_export(ft_strdup("SHLVL"), ft_strdup("1"), &export, data);
		return ;
	}
}

void	get_env_for_export(char **env, t_data *data)
{
	int		i;
	int		j;
	t_env	*export;

	export = NULL;
	data->env = env;
	export_without_env(data, export);
	i = 0 ;
	while (env[i])
	{
		if (!(env[i][0] == '_' && env[i][1] == '='))
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			add_export(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1,
					ft_strlen(env[i])), &export, data);
		}
		i++;
	}
	get_shlvl_export(data);
}
