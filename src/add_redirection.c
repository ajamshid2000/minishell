/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/18 14:35:46 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to add output redirection filename to the redirections structure */
void	add_output_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->out,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->out = ntab;
}

/* Main function decomposed into smaller functions*/
void	add_out(t_commands *commands, int id_cmd, char *filename)
{
	initialize_fcommand_array(commands);
	initialize_fcommand_element(commands, id_cmd);
	initialize_redirections(commands, id_cmd);
	add_output_redirection(commands, id_cmd, filename);
}

/* Function to add the filename to the append redirection list*/
void	add_append_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->append,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_out_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->append = ntab;
}

/* Main function decomposed into smaller functions */
void	add_append(t_commands *commands, int id_cmd, char *filename)
{
	initialize_fcommand_array(commands);
	initialize_fcommand_element(commands, id_cmd);
	initialize_redirections(commands, id_cmd);
	add_append_redirection(commands, id_cmd, filename);
}

/* Function to add the filename to the input redirection list */
void	add_input_redirection(t_commands *commands, int id_cmd, char *filename)
{
	char	**ntab;
	int		i;

	ntab = add_string_to_table(commands->fcommand[id_cmd]->redirections->in,
			filename);
	i = 0;
	while (ntab[i])
		i++;
	commands->fcommand[id_cmd]->redirections->last_in_name = ntab[i - 1];
	commands->fcommand[id_cmd]->redirections->in = ntab;
}
