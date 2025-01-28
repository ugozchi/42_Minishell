/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:39:33 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/23 17:14:15 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_sigint(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	g_waiting = 3;
	rl_done = 1;
	return ;
}

static void	handle_child_sigquit(int signum)
{
	(void)signum;
	write(2, "Quit (core dumped)\n", 20);
	g_waiting = 4;
	rl_done = 1;
	return ;
}

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	child_signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
	sa.sa_handler = handle_child_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, handle_child_sigquit);
	signal(SIGTSTP, SIG_IGN);
}
