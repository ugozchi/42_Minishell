/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:45 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 10:34:55 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_original_fd(int *original_fd)
{
	if (dup2(original_fd[0], STDIN_FILENO) == -1
		|| dup2(original_fd[1], STDOUT_FILENO) == -1)
	{
		close(original_fd[0]);
		close(original_fd[1]);
		perror("dup2 restore error");
		return (EXIT_FAILURE);
	}
	close(original_fd[0]);
	close(original_fd[1]);
	return (EXIT_SUCCESS);
}

static int	setup_original_fds(int *original_fd)
{
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	if (original_fd[0] == -1 || original_fd[1] == -1)
	{
		perror("dup error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	setup_redirections(int *fd_pipes, int pos, int *original_fd,
								t_data *data)
{
	if (setup_original_fds(original_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data->input.type == HEREDOC)
	{
		if (dup2(data->input.fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc error");
			close(original_fd[0]);
			close(original_fd[1]);
			return (EXIT_FAILURE);
		}
		close(data->input.fd);
	}
	else
	{
		if (dup2(fd_pipes[pos], STDIN_FILENO) == -1
			|| dup2(fd_pipes[pos + 3], STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			close(original_fd[0]);
			close(original_fd[1]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	execute_builtin(int *fd_pipes, int pos, t_commands *command, t_data *data)
{
	int	exit_code;
	int	original_fd[2];

	if (setup_redirections(fd_pipes, pos, original_fd, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close_unused_fd(fd_pipes, pos + 1);
	exit_code = launch_builtin(data, command, data->token, STDOUT_FILENO);
	close_fd(&fd_pipes[pos]);
	close_fd(&fd_pipes[pos + 3]);
	if (restore_original_fd(original_fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->exit_status = exit_code;
	return (exit_code);
}

int	execute_pipeline(int *fd_pipes, pid_t *pid, t_data *data)
{
	t_commands	*command;
	int			i;

	if (!fd_pipes || !pid || !data)
		return (EXIT_FAILURE);
	command = data->command;
	i = 0;
	while (command)
	{
		if (g_waiting == 3)
			break ;
		if (command_is_a_builtin(command))
			execute_builtin(fd_pipes, i * 2, command, data);
		else
			execute_env(fd_pipes, i * 2, &pid[i], data);
		i++;
		command = command->next;
	}
	finalize_child_processes(pid, i, data, fd_pipes);
	return (EXIT_SUCCESS);
}
