/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:12:09 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 16:11:00 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_longlong(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;
	unsigned long long	limit;

	i = 0;
	sign = 1;
	result = 0;
	limit = (unsigned long long)LLONG_MAX + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if ((sign == 1 && result > (unsigned long long)LLONG_MAX)
			|| (sign == -1 && result > limit))
			return (EXIT_FAILURE);
	}
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	exit_numeric_error(t_commands *command, t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(command->arg->value, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit_minishell(data, ft_atoi("2"));
}

static int	handle_too_many_args(t_data *data)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (data->exit_status = 1);
}

int	builtin_exit(t_commands *command, t_data *data)
{
	if (data->nb_pipe > 0)
		return (EXIT_SUCCESS);
	if (!command->arg)
		exit_minishell(data, EXIT_SUCCESS);
	if (command->arg && is_valid_longlong(command->arg->value)
		&& !command->arg->next)
		exit_numeric_error(command, data);
	if (command->arg && command->arg->next
		&& !is_valid_longlong(command->arg->value)
		&& !is_valid_longlong(command->arg->next->value))
		return (handle_too_many_args(data));
	if (command->arg && command->arg->next)
		exit_numeric_error(command, data);
	exit_minishell(data, ft_atoi(command->arg->value));
	return (EXIT_SUCCESS);
}
