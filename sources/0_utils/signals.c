/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:15:08 by melinamotyl       #+#    #+#             */
/*   Updated: 2025/01/23 17:15:18 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_waiting = 1;
}

void	signal_handlers(void)
{
	g_waiting = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_signal_handler(t_data *data)
{
	if ((g_waiting == 1 || g_waiting == 3)
		&& data->exit_status == 130)
	{
		g_waiting = 0;
		data->exit_status = 0;
	}
	if (g_waiting == 4 && data->exit_status == 131)
	{
		g_waiting = 0;
		data->exit_status = 0;
	}
}
