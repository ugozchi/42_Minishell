/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:06 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 18:11:37 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	putstr_fd(t_data *data, char *str_err, char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		putchar_fd(data, str_err, *s++, fd);
}

void	putchar_fd(t_data *data, char *str_err, char c, int fd)
{
	if (fd > -1)
	{
		if (write(fd, &c, 1) == -1)
		{
			putstr_fd(data, str_err, str_err, 2);
			putstr_fd(data, str_err,
				": write error : no space left on device\n", 2);
			return ;
		}
	}
}

static void	print_env(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		putstr_fd(data, "env", tmp->type, fd);
		putstr_fd(data, "env", "=", fd);
		putstr_fd(data, "env", tmp->value, fd);
		putstr_fd(data, "env", "\n", fd);
		tmp = tmp->next;
	}
}

int	builtin_env(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next && tok->next->type != PIPE)
	{
		ft_putstr_fd(INVALID_ARG_ENV, 2);
		data->exit_status += 1;
		return (EXIT_FAILURE);
	}
	else
	{
		print_env(data, fd_out);
		return (EXIT_SUCCESS);
	}
}
