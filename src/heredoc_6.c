/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/17 16:55:00 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	handle_child_exit_status(int status, char **heredoc_content,
		int *exec_flag, int *here_fd)
{
	status = WEXITSTATUS(status);
	if (status == 130)
	{
		if (*heredoc_content)
		{
			free(*heredoc_content);
			*heredoc_content = NULL;
		}
		*exec_flag = 0;
		close(*here_fd);
	}
}

int	initialize_heredoc_execution(char *delimiter, int *exec_flag, int *temp,
		int pipe_fd[2])
{
	(void)delimiter;
	*exec_flag = 1;
	(void)temp;
	if (setup_pipe(pipe_fd) == -1)
		return (-1);
	return (0);
}

pid_t	fork_heredoc_child(char *delimiter, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		heredoc_child(delimiter, pipe_fd);
	}
	return (pid);
}

void	handle_parent_process(pid_t pid, t_heredoc_params *params, int *here_fd)
{
	int	status;

	if (pid > 0)
	{
		close(params->pipe_fd[1]);
		*params->heredoc_content = read_heredoc_content(params->pipe_fd[0]);
		*here_fd = params->pipe_fd[0];
		waitpid(pid, &status, 0);
		handle_child_exit_status(status, params->heredoc_content,
			params->exec_flag, here_fd);
	}
	else
	{
		perror("fork");
	}
}

void	execute_heredoc(char *delimiter, char **heredoc_content, int *exec_flag,
		int *here_fd)
{
	t_heredoc_params	params;
	pid_t				pid;
	int					temp;

	g_signal_received = SIGUSR1;
	if (initialize_heredoc_execution(delimiter, exec_flag, &temp,
			params.pipe_fd) == -1)
		return ;
	params.heredoc_content = heredoc_content;
	params.exec_flag = exec_flag;
	params.temp = &temp;
	pid = fork_heredoc_child(delimiter, params.pipe_fd);
	g_signal_received = 0;
	handle_parent_process(pid, &params, here_fd);
}
