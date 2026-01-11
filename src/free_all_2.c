/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:23:29 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/17 18:23:30 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current->next)
	{
		if (current->env != NULL)
		{
			free(current->env[0]);
			if (current->env[1])
				free(current->env[1]);
			free(current->env);
		}
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
}
