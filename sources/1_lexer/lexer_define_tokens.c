/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:04 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 15:30:12 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_type	get_token_type(t_data *data, char symbol, int *is_new_command)
{
	if (symbol == '|')
	{
		*is_new_command = 1;
		return (PIPE);
	}
	if (symbol == '<' && *(data->line + 1) == '<')
	{
		data->line++;
		return (HEREDOC);
	}
	if (symbol == '>' && *(data->line + 1) == '>')
	{
		data->line++;
		return (APPEND);
	}
	if (symbol == '<')
		return (INPUT);
	if (symbol == '>')
		return (OUTPUT);
	return (-1);
}

static char	*resolve_by_norme(t_data *data, t_type *type)
{
	if (*type == HEREDOC)
	{
		if (*(data->line + 1) == '<')
			return (data->exit_status = 2, printf(H), NULL);
		return (ft_strdup("<<"));
	}
	else if (*type == PIPE)
	{
		if (*(data->line + 1) == '|')
			return (data->exit_status = 2, printf(P), NULL);
		return (ft_strdup("|"));
	}
	return (NULL);
}

char	*resolve_symbol_value(t_data *data, char symbol,
	int *is_new_command, t_type *type)
{
	*type = get_token_type(data, symbol, is_new_command);
	if (*type == APPEND)
	{
		if (*(data->line + 1) == '>')
			return (data->exit_status = 2, printf(A), NULL);
		return (ft_strdup(">>"));
	}
	else if (*type == INPUT)
		return (ft_strdup("<"));
	else if (*type == OUTPUT)
	{
		if (*(data->line + 1) == '<')
			return (data->exit_status = 2, printf(G), NULL);
		return (ft_strdup(">"));
	}
	return (resolve_by_norme(data, type));
}

t_token	*define_arg_type(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current)
	{
		if (current->type == OUTPUT || current->type == INPUT
			|| current->type == APPEND)
		{
			if (current->next && current->next->type == ARG)
				current->next->type = ARG_IN_OUT;
		}
		current = current->next;
	}
	return (token);
}

t_token	*define_tokens_exit_echo(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current)
	{
		if (current->type == CMD)
		{
			if (ft_strcmp(current->value, "exit") == 0
				|| ft_strcmp(current->value, "echo") == 0)
			{
				while (current->next && (current->next->type == FLAG
						|| current->next->type == ARG))
				{
					if (current->next && (current->next->type == FLAG))
						current->next->type = ARG;
					current = current->next;
				}
			}
		}
		current = current->next;
	}
	return (token);
}
