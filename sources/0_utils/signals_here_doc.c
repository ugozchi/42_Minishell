/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:43 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/22 12:09:11 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	signals_heredoc(void)
// {
// 	signal(SIGINT, heredoc_interrupt);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	heredoc_interrupt(int signum)
// {
// 	(void)signum;
// 	write(STDOUT_FILENO, "\n", 1);
// 	close(STDIN_FILENO);
// }

#include "minishell.h"

static void	handle_heredoc_sigint(int signum)
{
	(void)signum;
	g_waiting = 3;
	rl_done = 1;
	return ;
}

static int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	heredoc_signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_event;
	sa.sa_handler = handle_heredoc_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
