/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:05 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 12:51:21 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err_syntaxe(char err, int i)
{
	ft_putstr_fd("minishell: operation `", 2);
	while (i > 0)
	{
		ft_putchar_fd(err, 2);
		i--;
	}
	ft_putstr_fd("' not handle\n", 2);
}

static int	check_syntaxe_in_quote(char *line, int open_quote, int i,
		t_data *data)
{
	while (line[i])
	{
		if (!open_quote && (line[i] == '\'' || line[i] == '\"'))
		{
			data->wich_quote_err = line[i];
			open_quote = 1;
		}
		else if ((line[i] == '\"' || line[i] == '\'')
			&& line[i] == data->wich_quote_err)
		{
			open_quote = 0;
			data->wich_quote_err = '\0';
		}
		if ((line[i] == '\n' || line[i] == ';' || line[i] == '\\')
			&& !open_quote)
			return (print_err_syntaxe(line[i], 1), 1);
		if (((line[i] == '&' && line[i + 1] == '&')) && !open_quote)
			return (print_err_syntaxe(line[i], 2), 2);
		i++;
	}
	if (open_quote)
		return (3);
	return (0);
}

static int	open_quote_exit(t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(&data->wich_quote_err, 2);
	ft_putstr_fd("'\n", 2);
	return (EXIT_FAILURE);
}

void	syntaxe_line(char *line, t_data *data)
{
	int	i;

	if (!line)
		return ;
	data->wich_quote_err = '\0';
	i = check_syntaxe_in_quote(data->line, 0, 0, data);
	if (i)
	{
		data->exit_status = 2;
		if (i == 3)
			open_quote_exit(data);
		return ;
	}
}
