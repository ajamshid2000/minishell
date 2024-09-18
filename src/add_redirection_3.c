/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/09/12 09:05:22 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	add_end_text(t_commands *commands, int id_cmd, char *heredoc_content)
{
	if (!validate_inputs(commands, heredoc_content))
	{
		return ;
	}
	if (ensure_fcommand_capacity(commands, id_cmd) != 0)
	{
		return ;
	}
	if (commands->fcommand[id_cmd] == NULL)
	{
		commands->fcommand[id_cmd] = initialize_fcommand();
		if (!commands->fcommand[id_cmd])
		{
			return ;
		}
	}
	handle_heredoc_content(commands, id_cmd, heredoc_content);
}
