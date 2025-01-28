/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:54 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:58:55 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_is_a_builtin(t_commands *node)
{
	if (!ft_strcmp(node->command, "echo")
		|| !ft_strcmp(node->command, "cd")
		|| !ft_strcmp(node->command, "pwd")
		|| !ft_strcmp(node->command, "export")
		|| !ft_strcmp(node->command, "unset")
		|| !ft_strcmp(node->command, "env")
		|| !ft_strcmp(node->command, "exit"))
		return (1);
	else
		return (0);
}

int	launch_builtin(t_data *data, t_commands *node, t_token *token, int fd)
{
	int	exit_code;

	if (!ft_strcmp(node->command, "echo"))
		exit_code = builtin_echo(node, data);
	else if (!ft_strcmp(node->command, "cd"))
		exit_code = builtin_cd(node, data);
	else if (!ft_strcmp(node->command, "pwd"))
		exit_code = builtin_pwd(node, data);
	else if (!ft_strcmp(node->command, "export"))
		exit_code = builtin_export(data, token, fd);
	else if (!ft_strcmp(node->command, "unset"))
		exit_code = builtin_unset(data, token);
	else if (!ft_strcmp(node->command, "env"))
		exit_code = builtin_env(data, token, fd);
	else
		exit_code = builtin_exit(node, data);
	return (exit_code);
	return (0);
}
