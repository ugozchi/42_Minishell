/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:41 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 14:40:52 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_args(t_commands *commands)
{
	if (commands->flag != NULL)
	{
		ft_putstr_fd("pwd: usage: pwd\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*find_env_value(t_data *data, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], key, key_len)
			&& data->env[i][key_len] == '=')
			return (data->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_pwd(t_commands *commands, t_data *data)
{
	char	*cwd;

	(void)data;
	if (check_args(commands) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
