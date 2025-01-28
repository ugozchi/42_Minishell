/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:10 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 14:41:46 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	**env_extract_paths(t_env *env)
{
	char	**path_split;
	char	**path_split_full;
	int		i;

	while (env && ft_strcmp(env->type, "PATH") != 0)
		env = env->next;
	if (!env || !env->value)
		return (NULL);
	path_split = ft_split(env->value, ':');
	i = 0;
	while (path_split[i])
		i++;
	path_split_full = (char **)malloc((i + 1) * sizeof(char *));
	if (path_split_full)
	{
		path_split_full[i] = 0;
		while (--i >= 0)
			path_split_full[i] = ft_strjoin(path_split[i], "/");
	}
	free_char_array(path_split);
	return (path_split_full);
}

static char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*exec_path;

	i = -1;
	while (paths && paths[++i])
	{
		exec_path = ft_strjoin(paths[i], cmd);
		if (!exec_path)
			return (free_char_array(paths), NULL);
		if (access(exec_path, X_OK | F_OK) == 0)
			return (free_char_array(paths), exec_path);
		free(exec_path);
	}
	free_char_array(paths);
	return (NULL);
}

static char	*try_direct_command(t_data *data, char *cmd)
{
	char	*exec_path;

	exec_path = ft_strdup(cmd);
	if (!exec_path)
		return (NULL);
	if (access(exec_path, X_OK | F_OK) == 0)
		return (exec_path);
	data->exit_status = 127;
	ft_putstr_fd(CMD_NOT_FOUND, 2);
	ft_putendl_fd(cmd, 2);
	free(exec_path);
	return (NULL);
}

char	*search_cmd_path(t_data *data, t_commands *cmd)
{
	char		*exec_path;
	char		**paths;
	struct stat	path_stat;

	if (!cmd || !data->cpy_env || !cmd->command[0])
		return (NULL);
	if (stat(cmd->command, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		data->exit_status = 126;
		ft_putstr_fd(cmd->command, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (NULL);
	}
	paths = env_extract_paths(data->cpy_env);
	exec_path = try_paths(paths, cmd->command);
	if (exec_path)
		return (exec_path);
	return (try_direct_command(data, cmd->command));
}

int	command_executer(t_commands *command, t_data *data)
{
	char	*exec_path;

	if (!command || !command->command)
		return (EXIT_FAILURE);
	exec_path = NULL;
	exec_path = search_cmd_path(data, command);
	data->new_env = env_to_tab(data->cpy_env);
	if (exec_path)
		data->exit_status = execve(exec_path, command->final_group,
				data->new_env);
	free(exec_path);
	exit(data->exit_status);
}
