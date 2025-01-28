/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:01 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:59:04 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' || str[1] != 'n')
		return (1);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

static void	print_echo(char **array, int flag, int pos)
{
	int	first;

	first = 1;
	while (array[pos])
	{
		if (ft_strlen(array[pos]) == 0)
		{
			pos++;
			continue ;
		}
		if (first)
		{
			printf("%s", array[pos]);
			first = 0;
		}
		else
			printf(" %s", array[pos]);
		pos++;
	}
	if (!flag)
		printf("\n");
}

int	builtin_echo(t_commands *commands, __attribute__((unused)) t_data *data)
{
	int		pos;
	int		flag;

	flag = 0;
	pos = 1;
	while (commands->final_group[pos])
	{
		if (!check_valid_flag(commands->final_group[pos]))
		{
			flag = 1;
			pos++;
		}
		else
			break ;
	}
	print_echo(commands->final_group, flag, pos);
	return (EXIT_SUCCESS);
}
