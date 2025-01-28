/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:15 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/24 14:41:34 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(t_commands *cmds)
{
	int			i;
	t_commands	*ptr;

	i = 0;
	ptr = cmds;
	while (ptr && ++i)
		ptr = ptr->next;
	return (i);
}

int	executer(t_data *data)
{
	int		cmds_num;

	cmds_num = cmd_count(data->command);
	data->pid = (pid_t *)ft_calloc(cmds_num, sizeof(pid_t));
	if (!data->pid)
		return (EXIT_FAILURE);
	data->nb_pipe = cmds_num - 1;
	data->fd_pipes = build_pipes(data->output.fd, data->input.fd, cmds_num);
	if (!data->fd_pipes)
		return (free(data->pid), data->pid = NULL, EXIT_FAILURE);
	child_signal_handler();
	execute_pipeline(data->fd_pipes, data->pid, data);
	free(data->fd_pipes);
	data->fd_pipes = NULL;
	free(data->pid);
	data->pid = NULL;
	return (EXIT_SUCCESS);
}
