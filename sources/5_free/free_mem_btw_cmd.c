/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_btw_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:00:04 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/21 16:34:03 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_in_out(t_data *data)
{
	data->input.type = STDIN;
	if (data->input.value)
	{
		free(data->input.value);
		data->input.value = NULL;
	}
	data->input.fd = 0;
	data->output.type = STDOUT;
	if (data->output.value)
	{
		free(data->output.value);
		data->output.value = NULL;
	}
	data->output.fd = 1;
}

void	free_command(t_data *data)
{
	t_commands	*temp;

	while (data->command != NULL)
	{
		temp = data->command;
		data->command = data->command->next;
		temp->next = NULL;
		if (temp->command)
		{
			free(temp->command);
			temp->command = NULL;
		}
		if (temp->flag)
			free_list(temp->flag);
		if (temp->arg)
			free_list(temp->arg);
		if (temp->final_group)
			free_char_array(temp->final_group);
		free(temp);
		temp = NULL;
	}
}

void	free_token(t_data *data)
{
	t_token	*temp;

	while (data->token != NULL)
	{
		temp = data->token;
		data->token = data->token->next;
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (temp)
			free(temp);
		temp = NULL;
	}
}

void	free_mem_between_cmd(t_data *data)
{
	if (data->expanded_str)
	{
		free(data->expanded_str);
		data->expanded_str = NULL;
	}
	free_command(data);
	free_token(data);
	free_in_out(data);
}
