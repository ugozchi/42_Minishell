/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:10 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 15:17:42 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
	{
		ft_memcpy(new_str, str, len);
		free(str);
		str = NULL;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

int	lexer_core(t_data *data, t_quote *current_quote,
			char **current_token, int *is_new_command)
{
	while (*data->line)
	{
		if (*current_quote == NQ)
		{
			if (!no_quote(data, current_quote, current_token, is_new_command))
				return (EXIT_FAILURE);
		}
		else if (*current_quote == SQ)
		{
			if (!single_quote(data, current_quote, current_token))
				return (EXIT_FAILURE);
		}
		else if (*current_quote == DQ)
		{
			if (!double_quote(data, current_quote, current_token))
				return (EXIT_FAILURE);
		}
		data->line++;
	}
	return (EXIT_SUCCESS);
}

static int	if_no_good_pipe(t_data *data)
{
	t_token	*pipe;

	pipe = data->token;
	while (pipe)
	{
		if (pipe->type == PIPE)
		{
			if (data->token == pipe && pipe->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
				data->exit_status = 2;
				free_token(data);
				return (EXIT_FAILURE);
			}
			else if (pipe->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				data->exit_status = 2;
				free_token(data);
				return (EXIT_FAILURE);
			}
		}
		pipe = pipe->next;
	}
	return (EXIT_SUCCESS);
}

int	lexer_finalize(t_data *data, t_quote current_quote,
		char **current_token, int is_new_command)
{
	if (current_quote != NQ)
	{
		ft_putstr_fd("minishell: syntax error: quotes not closed\n", 2);
		data->exit_status = 2;
		free(*current_token);
		free_token(data);
		return (EXIT_FAILURE);
	}
	if (*current_token && **current_token)
	{
		if (!create_and_add_token(data, *current_token, &is_new_command))
			return (EXIT_FAILURE);
		*current_token = NULL;
	}
	if (!mark_heredoc_tokens(data->token) || !mark_input_tokens(data->token))
	{
		free(*current_token);
		free_token(data);
		return (EXIT_FAILURE);
	}
	define_tokens_exit_echo(data->token);
	define_arg_type(data->token);
	if_no_good_pipe(data);
	return (EXIT_SUCCESS);
}

int	lexer(t_data *data, int is_new_command)
{
	t_quote	current_quote;
	char	*current_token;
	int		ret;

	current_quote = NQ;
	current_token = NULL;
	ret = lexer_core(data, &current_quote, &current_token, &is_new_command);
	if (ret != EXIT_SUCCESS)
		return (ret);
	return (lexer_finalize(data, current_quote, &current_token,
			is_new_command));
}
