/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:27:49 by famana            #+#    #+#             */
/*   Updated: 2024/10/16 09:17:46 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to disable Ctrl-\ (SIGQUIT) */
void	disable_quit_signal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/* Alternatively, if you want to restore the full original settings */
void	restore_original_terminal_settings(struct termios *original_term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original_term) == -1)
	{
		perror("tcsetattr failed");
	}
}

/* Function to re-enable Ctrl-\ (SIGQUIT) */
void	enable_quit_signal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr failed");
		return ;
	}
	term.c_cc[VQUIT] = 034;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr failed");
	}
}
