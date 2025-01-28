/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:56 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/22 10:44:04 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_data *data, t_env *env, int cpy)
{
	t_env	*tmp;

	if (cpy == 1 && !data->cpy_env)
		return ;
	if (cpy == 2 && !data->export)
		return ;
	tmp = env;
	while (env)
	{
		tmp = env->next;
		if (env->type)
			free(env->type);
		if (env->value)
			free(env->value);
		env->type = NULL;
		env->value = NULL;
		free(env);
		env = tmp;
	}
	if (cpy == 1)
		data->cpy_env = NULL;
	else if (cpy == 2)
		data->export = NULL;
}

void	free_all_memory(t_data *data)
{
	if (!data)
		return ;
	free_env(data, data->cpy_env, 1);
	free_env(data, data->export, 2);
	free_char_array(data->path);
	if (data->expanded_str)
	{
		free(data->expanded_str);
		data->expanded_str = NULL;
	}
	if (data->line && ft_strcmp(data->token->value, "exit"))
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->full_path)
	{
		free(data->full_path);
		data->full_path = NULL;
	}
	free_token(data);
	free_command(data);
	free_in_out(data);
}
