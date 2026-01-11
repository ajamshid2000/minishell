/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/18 12:32:27 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Helper function to handle signal interruption*/
static void	handle_signal_interrupt(char *line, int pipe_fd)
{
	if (line)
	{
		close(pipe_fd);
		free(line);
		line = NULL;
	}
	g_signal_received = 0;
	exit(130);
}

/* Helper function to handle end of file (Ctrl-D) in heredoc*/
static void	handle_eof(int pipe_fd[2])
{
	close(pipe_fd[1]);
	exit(100);
}

/* Helper function to handle a matching delimiter*/
static int	check_delimiter(char *line, char *delimiter)
{
	if (strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

/* Helper function to write heredoc line to the pipe*/
static void	write_heredoc_line_to_pipe(char *line, int pipe_fd[2])
{
	write(pipe_fd[1], line, ft_strlen(line));
	write(pipe_fd[1], "\n", 1);
}

/* Function to handle heredoc input in child process*/
void	heredoc_child(char *delimiter, int pipe_fd[2])
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			ft_printf("warning: here-document delimited by end-of-file (wanted"
				" %s)\n", delimiter);
		if (g_signal_received == SIGINT)
			handle_signal_interrupt(line, pipe_fd[1]);
		if (!line)
			handle_eof(pipe_fd);
		if (check_delimiter(line, delimiter))
			break ;
		write_heredoc_line_to_pipe(line, pipe_fd);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}
