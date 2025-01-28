/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_tokens2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:30:27 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/24 15:30:19 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_symbol_token(t_data *data, char symbol, int *is_new_command)
{
	t_type	type;
	char	*value;

	value = resolve_symbol_value(data, symbol, is_new_command, &type);
	if (!value)
		return (0);
	return (create_and_add_symbol_token(data, value, type));
}

int	check_double_tokens(char *str)
{
	if (!ft_strchr(SUPPORTED_SYMBOLS, *(str + 1)))
		return (EXIT_SUCCESS);
	else
	{
		if ((*str == '<' && *(str + 1) == '<') || (*str == '>' && *(str
					+ 1) == '>'))
			return (EXIT_SUCCESS);
		else
		{
			printf("Syntax error: unexpected token %c after token %c\n",
				*(str + 1), *str);
			return (EXIT_FAILURE);
		}
	}
}

int	create_and_add_symbol_token(t_data *data, char *value, t_type type)
{
	t_token	*new;

	new = new_token(value, value + ft_strlen(value), type, NQ);
	if (!new)
		return (0);
	lst_token_add_back(data, new);
	return (1);
}

t_token	*mark_heredoc_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == HEREDOC && current->next)
		{
			if (current->next->type != ARG && current->next->type != CMD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token\n",
					2);
				ft_putstr_fd("invalid heredoc delimiter\n", 2);
				return (NULL);
			}
			current->next->type = LIM;
			if (current->next->next && current->next->next->type == ARG
				&& !current->prev)
				current->next->next->type = CMD;
		}
		current = current->next;
	}
	return (token);
}

t_token	*mark_input_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == INPUT && current->next)
		{
			if (current->next->type != ARG && current->next->type != ARG_IN_OUT
				&& current->next->type != CMD)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				return (NULL);
			}
			current->next->type = ARG_IN_OUT;
			if (current->next->next
				&& !current->prev)
				current->next->next->type = CMD;
		}
		current = current->next;
	}
	return (token);
}
