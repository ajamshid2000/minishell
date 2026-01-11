/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:58:30 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/18 13:51:35 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	execute_cur_command(t_commands *commands, int **pipe_fd, int j, int i)
{
	int	original_stdout;

	(void)j;
	if ((!is_builtin(commands->fcommand[i]->command)
			&& commands->pipe_count == 0))
	{
		original_stdout = dup(1);
		if (commands->fcommand[i]->redirections
			&& commands->fcommand[i]->redirections->last_out != 0)
			redirect_out(commands, i, pipe_fd[i][1]);
		execute_builtin(commands->env, commands, i, 1);
		close(pipe_fd[i][1]);
		dup2(original_stdout, 1);
		close(original_stdout);
		commands->j--;
	}
	else if (i == 0 && i == commands->pipe_count)
		execute_command(commands, i, 0, 1);
	else if (i == 0)
		execute_command(commands, i, 0, pipe_fd[i][1]);
	else if (i == commands->pipe_count)
		execute_command(commands, i, pipe_fd[i - 1][0], 1);
	else
		execute_command(commands, i, pipe_fd[i - 1][0], pipe_fd[i][1]);
}

int	execute_and_redirect(t_commands *commands, int **pipe_fd, int i)
{
	t_fcommand	*command;
	int			set_fd_return_value;

	set_fd_return_value = commands->fcommand[i]->error;
	(void)command;
	commands->status = set_fd_return_value;
	if (set_fd_return_value == 1)
	{
		close(pipe_fd[i][1]);
		return (-1);
	}
	else
	{
		execute_cur_command(commands, pipe_fd, set_fd_return_value, i);
	}
	return (0);
}

int	close_pipes_and_wait(t_commands *commands, int i)
{
	free_pipe(commands);
	i = 0;
	while (i <= commands->j)
	{
		if (i == 0)
			enable_quit_signal();
		if (!commands->status)
		{
			wait(&commands->status);
			commands->status = WEXITSTATUS(commands->status);
		}
		else
			wait(0);
		if (i == 0 && g_signal_received == SIGINT)
			commands->status = 130;
		if (i == 0 && g_signal_received == SIGQUIT)
		{
			ft_putstr_fd("Quit ( dumped)\n", 1);
			commands->status = 130;
		}
		i++;
	}
	return (0);
}

int	execute_pipe(t_commands *commands)
{
	int	i;

	commands->j = commands->pipe_count;
	commands->pipe_fd = (int **)malloc(sizeof(int *) * (commands->pipe_count
				+ 2));
	if (!commands->pipe_fd)
		return (0);
	i = 0;
	while (i <= commands->pipe_count + 1)
	{
		commands->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!commands->pipe_fd)
			return (0);
		pipe(commands->pipe_fd[i]);
		i++;
	}
	i = 0;
	while (i <= commands->pipe_count)
	{
		if (execute_and_redirect(commands, commands->pipe_fd, i) == -1)
			commands->j--;
		i++;
	}
	close_pipes_and_wait(commands, i);
	return (0);
}

int	execute_pipes(t_commands *commands)
{
	int	i;

	i = -1;
	while (commands->fcommand[++i])
	{
		if (is_builtin(commands->fcommand[i]->command)
			&& !ft_strchr(commands->fcommand[i]->command[0], '/'))
			commands->fcommand[i]->command[0] = find_path(commands->env,
					commands->fcommand[i]->command);
	}
	execute_pipe(commands);
	if (commands->fcommand[i - 1]->command && commands->fcommand[i
			- 1]->command[0]
		&& !ft_strcmp(commands->fcommand[i - 1]->command[0],
			"exit"))
	{
		return (exit_minishell(commands, i));
	}
	return (0);
}
