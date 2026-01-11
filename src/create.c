/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:25:52 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/17 16:03:21 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_env	*create_env_stack(void)
{
	t_env		*env;
	t_env		*temp;
	int			i;
	extern char	**environ;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (0);
	temp = env;
	i = 0;
	while (environ[i])
	{
		temp->env = ft_split_one(environ[i], '=');
		temp->next = (t_env *)malloc(sizeof(t_env));
		if (!temp->next)
		{
			free_env(env);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	temp->env = NULL;
	temp->next = NULL;
	return (env);
}

int	create_array(t_env *temp, char **enva, int i)
{
	char	*temps;

	if (temp->env[0] && temp->env[1])
	{
		temps = ft_strjoin(temp->env[0], "=");
		enva[i] = ft_strjoin(temps, temp->env[1]);
		free(temps);
		return (0);
	}
	return (1);
}

char	**create_env_array(t_env *env)
{
	int		i;
	char	**enva;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp && temp->next)
	{
		temp = temp->next;
		i++;
	}
	enva = (char **)malloc(sizeof(char *) * (i + 1));
	if (!enva)
		return (NULL);
	i = 0;
	temp = env;
	while (temp->next)
	{
		if (!create_array(temp, enva, i))
			i++;
		temp = temp->next;
	}
	enva[i] = NULL;
	return (enva);
}
