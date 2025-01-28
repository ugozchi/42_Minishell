/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execute2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinaaam <melinaaam@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:20:04 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/23 15:27:55 by melinaaam        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_env_execution(int *fd_pipes, int pos, t_data *data,
									t_commands **cmd)
{
	t_commands	*current_cmd;
	int			cmd_count;

	(void)fd_pipes;
	current_cmd = data->command;
	cmd_count = 0;
	while (current_cmd && cmd_count++ *2 < pos)
		current_cmd = current_cmd->next;
	if (!current_cmd || !current_cmd->command)
		return (EXIT_FAILURE);
	*cmd = current_cmd;
	return (EXIT_SUCCESS);
}

static int	prepare_exec_path(t_data *data, t_commands *cmd, char **exec_path)
{
	*exec_path = search_cmd_path(data, cmd);
	if (!(*exec_path))
		return (EXIT_FAILURE);
	free(*exec_path);
	return (EXIT_SUCCESS);
}

static int	create_child_process(int *fd_pipes, int pos, t_data *data,
									t_commands *cmd)
{
	if (dup2(fd_pipes[pos], STDIN_FILENO) == -1
		|| dup2(fd_pipes[pos + 3], STDOUT_FILENO) == -1)
	{
		perror("dup2 in child error");
		exit(EXIT_FAILURE);
	}
	close_unused_fd(fd_pipes, pos);
	exit(command_executer(cmd, data));
}

int	execute_env(int *fd_pipes, int pos, int *pid, t_data *data)
{
	t_commands	*cmd;
	char		*exec_path;

	if (setup_env_execution(fd_pipes, pos, data, &cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (prepare_exec_path(data, cmd, &exec_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork error");
		return (EXIT_FAILURE);
	}
	if (*pid == 0)
		create_child_process(fd_pipes, pos, data, cmd);
	close_fd(&fd_pipes[pos]);
	close_fd(&fd_pipes[pos + 3]);
	return (EXIT_SUCCESS);
}
