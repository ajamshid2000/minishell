/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/17 16:52:29 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_commands	*handle_output_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_out(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_append_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_append(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_input_redirection(t_commands *commands,
		char **splited_command, int *i, int id_cmd)
{
	(*i)++;
	return (add_in(commands, id_cmd, splited_command[*i]));
}

t_commands	*handle_heredoc_redirection(t_commands *commands,
		char ***splited_command, int *i, int id_cmd)
{
	char	*heredoc;
	int		exec_flag;
	int		here_fd;

	here_fd = 0;
	exec_flag = 1;
	(*i)++;
	heredoc = handle_heredoc2((*splited_command)[*i], &exec_flag, &here_fd);
	if (heredoc == NULL && exec_flag == 0)
	{
		my_free_cmd(commands);
		free_split(*splited_command);
		*splited_command = NULL;
		return (NULL);
	}
	if (heredoc == NULL && exec_flag == 1)
	{
		my_free_cmd(commands);
		printf("Memory allocation for heredoc failed!\n");
		return (NULL);
	}
	commands = add_end_text(commands, id_cmd, heredoc);
	commands->fcommand[id_cmd]->redirections->here_fd = here_fd;
	free(heredoc);
	return (commands);
}

t_commands	*handle_redirections(t_commands *commands, char ***splited_command,
		int *i, int id_cmd)
{
	if (ft_strcmp((*splited_command)[*i], ">") == 0)
		return (handle_output_redirection(commands, *splited_command, i,
				id_cmd));
	else if (ft_strcmp((*splited_command)[*i], ">>") == 0)
		return (handle_append_redirection(commands, *splited_command, i,
				id_cmd));
	else if (ft_strcmp((*splited_command)[*i], "<") == 0)
		return (handle_input_redirection(commands, *splited_command, i,
				id_cmd));
	else if (ft_strcmp((*splited_command)[*i], "<<") == 0)
		return (handle_heredoc_redirection(commands, splited_command, i,
				id_cmd));
	return (commands);
}
