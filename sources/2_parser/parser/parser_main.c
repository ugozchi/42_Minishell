/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:57 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 15:59:50 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	open_redirection_fd(t_data *data, t_in_out *redir, t_token *token,
// 		int oflag)
// {
// 	(void)(data);
// 	if (redir->fd >= 3)
// 		close(redir->fd);
// 	if (!token->next)
// 		return (perror_return("syntax error near unexpected token "));
// 	redir->type = token->type;
// 	redir->quote = token->quote;
// 	if (redir->value)
// 		free(redir->value);
// 	redir->value = ft_strdup(token->next->value);
// 	if (!redir->value)
// 		return (perror_return("ft_strdup for redirection value"));
// 	if (redir->type != HEREDOC)
// 	{
// 		redir->fd = open(redir->value, oflag, 0644);
// 		if (redir->fd < 0)
// 			return (perror_return("No such file or directory"));
// 	}
// 	else if (redir->type == HEREDOC)
// 	{
// 		g_waiting = 2;
// 		redir->fd = open("heredoc.tmp", oflag, 0644);
// 		if (redir->fd < 0)
// 			return (perror_return(redir->value));
// 		heredoc_signal_handler();
// 	}
// 	return (EXIT_SUCCESS);
// }

static int	open_and_handle_redirection(t_in_out *redir, t_token *token,
										int oflag)
{
	redir->type = token->type;
	redir->quote = token->quote;
	if (redir->value)
		free(redir->value);
	redir->value = ft_strdup(token->next->value);
	if (!redir->value)
		return (perror_return("ft_strdup for redirection value"));
	if (redir->type != HEREDOC)
	{
		redir->fd = open(redir->value, oflag, 0644);
		if (redir->fd < 0)
			return (perror_return("No such file or directory"));
	}
	else
	{
		g_waiting = 2;
		redir->fd = open("heredoc.tmp", oflag, 0644);
		if (redir->fd < 0)
			return (perror_return(redir->value));
		heredoc_signal_handler();
	}
	return (EXIT_SUCCESS);
}

int	open_redirection_fd(t_data *data, t_in_out *redir, t_token *token,
						int oflag)
{
	(void)(data);
	if (redir->fd >= 3)
		close(redir->fd);
	if (!token->next)
		return (perror_return("syntax error near unexpected token "));
	return (open_and_handle_redirection(redir, token, oflag));
}

int	parser_helper_redirections(t_data *data, t_token *token)
{
	if (token->type == HEREDOC)
	{
		if (!token->next || token->next->type != LIM)
			return (ft_putstr_fd(M, 2), EXIT_FAILURE);
		if (here_doc(data, token->next->value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (token->type == INPUT)
	{
		if (open_redirection_fd(data, &data->input, token, O_RDONLY))
			return (2);
	}
	else if (token->type == OUTPUT)
	{
		if (open_redirection_fd(data, &data->output, token,
				O_WRONLY | O_TRUNC | O_CREAT))
			return (EXIT_FAILURE);
	}
	else if (token->type == APPEND)
	{
		if (open_redirection_fd(data, &data->output, token,
				O_WRONLY | O_APPEND | O_CREAT))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_helper_others(t_data *data, t_token *token, int *create_new_node)
{
	static t_commands	*ptr = NULL;

	if (*create_new_node)
	{
		ptr = add_new_command_node(data);
		*create_new_node = 0;
		if (!ptr)
			return (EXIT_FAILURE);
		if (!populate_node_command(ptr, token))
			return (EXIT_FAILURE);
	}
	else if (token->value[0] == '-' && token->type == FLAG)
	{
		if (populate_node_flag(ptr, token))
			return (EXIT_FAILURE);
	}
	else if (token->type == ARG)
	{
		comp_value_token(data, token);
		if (populate_node_argument(ptr, token))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser(t_data *data)
{
	t_token	*ptr;
	int		create_new_node;

	ptr = data->token;
	create_new_node = 1;
	while (ptr)
	{
		if (ptr->type == PIPE)
			create_new_node = 1;
		else if (ptr->type == CMD || ptr->type == ARG || ptr->type == FLAG)
			parser_helper_others(data, ptr, &create_new_node);
		else
		{
			if (parser_helper_redirections(data, ptr))
				return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	if (create_new_node && *data->line)
		return (ft_printf_exit_code("No command after pipe\n", EXIT_FAILURE));
	if (concate_final_group_commands(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
