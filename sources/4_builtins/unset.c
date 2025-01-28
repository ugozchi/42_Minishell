/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:51 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 10:33:18 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->cpy_env;
	if (delete == start)
	{
		data->cpy_env = data->cpy_env->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	unset_export_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->export;
	if (delete == start)
	{
		data->export = data->export->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	find_node_to_unset(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_env_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	find_node_to_unset2(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_export_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_data *data, t_token *token)
{
	t_token	*tmp_tok;

	tmp_tok = token->next;
	while (tmp_tok && tmp_tok->type == ARG)
	{
		if (tmp_tok->value)
		{
			find_node_to_unset(data->cpy_env, data, tmp_tok->value);
			find_node_to_unset2(data->export, data, tmp_tok->value);
		}
		tmp_tok = tmp_tok->next;
	}
	return (EXIT_SUCCESS);
}
