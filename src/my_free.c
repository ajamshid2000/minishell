/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/16 10:36:37 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// Helper function to free a NULL-terminated array of strings
static void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Helper function to free the t_redirections structure
static void	free_redirections2(t_redirections *redir)
{
	if (!redir)
		return ;
	if (redir->last_in_name)
		free(redir->last_in_name);
	if (redir->last_out_name)
		free(redir->last_out_name);
	if (redir->here)
		free(redir->here);
	if (redir->append)
		free_string_array(redir->append);
	if (redir->in)
		free_string_array(redir->in);
	if (redir->out)
		free_string_array(redir->out);
	free(redir);
}

// Helper function to free the t_fcommand structure
void	free_fcommand(t_fcommand *fcmd)
{
	if (!fcmd)
		return ;
	if (fcmd->command)
		free_string_array(fcmd->command);
	if (fcmd->redirections)
		free_redirections2(fcmd->redirections);
	free(fcmd);
}

void	my_free_cmd(t_commands *commands)
{
	int	i;

	i = 0;
	if (!commands)
		return ;
	free_redirections(commands);
	if (commands->fcommand)
	{
		while (commands->fcommand[i])
		{
			free_table(commands->fcommand[i]->command);
			free(commands->fcommand[i]);
			i++;
		}
		free(commands->fcommand);
	}
	free(commands);
}

void	free_input_split(char *input, char **splited_command)
{
	int	i;

	i = 0;
	if (splited_command != NULL)
	{
		while (splited_command[i] != NULL)
		{
			free(splited_command[i]);
			i++;
		}
		free(splited_command);
	}
	if (input != NULL)
	{
		free(input);
	}
}
