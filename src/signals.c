/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:27:49 by famana            #+#    #+#             */
/*   Updated: 2024/10/18 13:04:39 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (!g_signal_received)
	{
		write(STDOUT_FILENO, "^C", 2);
		g_signal_received = SIGINT;
	}
	else if (g_signal_received == SIGUSR2)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal_received = SIGINT;
	}
	g_signal_received = SIGINT;
}

int	my_event_hook(void)
{
	if (g_signal_received && g_signal_received != SIGUSR1
		&& g_signal_received != SIGUSR2)
	{
		rl_done = 1;
	}
	return (0);
}

void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p))
		perror("minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p))
		perror("minishell: tcsetattr");
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_signal_received = SIGQUIT;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction SIGINT");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		exit(EXIT_FAILURE);
	}
}
