/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:57 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/23 16:59:18 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_check_args(t_commands *commands)
{
	if (commands->flag)
		return (ft_printf_exit_code(CD_ERR_FLAGS, EXIT_FAILURE));
	if (commands->arg && commands->arg->next)
		return (ft_printf_exit_code(CD_ERR_ARG, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static char	*cd_resolve_path(t_commands *commands, t_data *data)
{
	char	*path;

	if (!commands->arg)
	{
		path = find_env_value(data, "HOME");
		if (!path)
			ft_putstr_fd(CD_ERR_HOME, STDERR_FILENO);
	}
	else if (!ft_strcmp(commands->arg->value, "-"))
	{
		path = find_env_value(data, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd(CD_ERR_OLDPWD, STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = commands->arg->value;
	return (path);
}

static int	cd_set_env(t_data *data, const char *key, const char *value)
{
	t_env	*temp;

	if (!key || !value)
		return (EXIT_FAILURE);
	temp = data->cpy_env;
	while (temp)
	{
		if (!ft_strcmp(temp->type, key) && temp->equal == '=')
		{
			free(temp->value);
			temp->value = ft_strdup(value);
		}
		temp = temp->next;
	}
	temp = data->export;
	while (temp)
	{
		if (!ft_strcmp(temp->type, key) && temp->equal == '=')
		{
			free(temp->value);
			temp->value = ft_strdup(value);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static int	cd_update_vars(t_data *data, const char *old_pwd,
		const char *new_pwd)
{
	if (cd_set_env(data, "OLDPWD", old_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cd_set_env(data, "PWD", new_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_commands *commands, t_data *data)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	if (cd_check_args(commands))
		return (EXIT_FAILURE);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror_return("getcwd error"));
	path = cd_resolve_path(commands, data);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
		return (perror_return("chdir error"));
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror_return("getcwd error"));
	if (cd_update_vars(data, old_pwd, new_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
