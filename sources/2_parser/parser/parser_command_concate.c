/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_concate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:47 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 12:42:39 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	get_number_of_command_elements(t_commands *node)
{
	size_t	count;
	t_list	*arg_ptr;
	t_list	*flag_ptr;

	count = 1;
	arg_ptr = node->arg;
	flag_ptr = node->flag;
	while (arg_ptr)
	{
		count++;
		arg_ptr = arg_ptr->next;
	}
	while (flag_ptr)
	{
		count++;
		flag_ptr = flag_ptr->next;
	}
	return (count);
}

int	add_cmd_to_final_group(t_commands *command_ptr, size_t *i)
{
	command_ptr->final_group[*i] = ft_strdup(command_ptr->command);
	if (!command_ptr->final_group[*i])
		return (perror_return("add_cmd_to_final_group malloc"));
	(*i)++;
	return (EXIT_SUCCESS);
}

int	add_args_to_final_group(t_commands *command_ptr, size_t *i)
{
	t_list	*arg;

	arg = command_ptr->arg;
	while (arg)
	{
		command_ptr->final_group[*i] = ft_strdup(arg->value);
		if (!command_ptr->final_group[*i])
			return (perror_return("add_args_to_final_group malloc"));
		(*i)++;
		arg = arg->next;
	}
	return (EXIT_SUCCESS);
}

int	add_flags_to_final_group(t_commands *command_ptr, size_t *i)
{
	t_list	*flag;

	flag = command_ptr->flag;
	while (flag)
	{
		command_ptr->final_group[*i] = ft_strdup(flag->value);
		if (!command_ptr->final_group[*i])
			return (perror_return("add_flags_to_final_group malloc"));
		(*i)++;
		flag = flag->next;
	}
	return (EXIT_SUCCESS);
}

int	concate_final_group_commands(t_data *data)
{
	t_commands	*command_ptr;
	size_t		number_of_elements;
	size_t		i;

	command_ptr = data->command;
	while (command_ptr)
	{
		number_of_elements = get_number_of_command_elements(command_ptr);
		command_ptr->final_group = malloc(sizeof(char *) * (number_of_elements
					+ 1));
		if (!command_ptr->final_group)
			return (perror_return("final_group malloc failed"));
		i = 0;
		if (add_cmd_to_final_group(command_ptr, &i)
			|| add_args_to_final_group(command_ptr, &i)
			|| add_flags_to_final_group(command_ptr, &i))
			return (EXIT_FAILURE);
		command_ptr->final_group[i] = NULL;
		command_ptr = command_ptr->next;
	}
	return (EXIT_SUCCESS);
}
