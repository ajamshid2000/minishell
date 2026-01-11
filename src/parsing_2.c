/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/18 13:55:39 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	process_redirections_pipes(char **splited_command, char *spaced,
		int *status, char *input)
{
	if (!check_redirections_and_pipes(splited_command, spaced))
	{
		free_input_split(input, splited_command);
		free(spaced);
		*status = 2;
		return (0);
	}
	free(spaced);
	return (1);
}

int	prepare_command(char *input, char **spaced, char ***splited_command)
{
	return (allocate_and_check_memory(input, spaced, splited_command));
}

int	handle_rec_check(char *input, int check, int *status)
{
	return (if_check_is_1(input, check, status));
}

int	handle_quotes_and_spaces(char *input, int *status)
{
	if (is_only_space(input) == 1)
		return (free_input_and_set_status(input, status, 0));
	if (has_unclosed_quotes(input) == 1)
	{
		printf("error unclosed quotes or double quotes\n");
		return (free_input_and_set_status(input, status, 0));
	}
	return (0);
}

char	*expand_variables_and_replace(char *input, t_env *env, int status)
{
	return (expand_and_replace_variables_string(env, input, status));
}
