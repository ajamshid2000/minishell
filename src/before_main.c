/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:27:49 by famana            #+#    #+#             */
/*   Updated: 2024/10/17 17:54:32 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to process the input and handle history*/
int	process_input(char *input, t_env *env, int *status)
{
	int	exit_flag;
	int	i;

	exit_flag = 0;
	if (*input)
	{
		add_history(input);
		i = 0;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			return (0);
		exit_flag = eval2(input, env, status);
	}
	return (exit_flag);
}
/*
int	main(void)
{
	char	*input;
	int		exit_flag;
	t_env	*env;
	int		status;

	status = 0;
	env = create_env_stack();
	exit_flag = 0;
	rl_event_hook = my_event_hook;
	while (1)
	{
		g_ctrl_c_status = 0;
		rl_event_hook = my_event_hook;
		rl_catch_signals = 0;
		setup_signal_handlers();
		disable_quit_signal();
		input = readline("minishell> ");
		if (g_signal_received == SIGINT)
		{
			if (input)
			{
				free(input);
				input = NULL;
			}
			g_signal_received = 0;
			status = 130;
			continue ;
		}
		if (input == NULL)
			break ;
		exit_flag = process_input(input, env, &status);
		disable_quit_signal();
		g_signal_received = 0;
		if (exit_flag == 1)
			break ;
	}
	free_env(env);
	rl_clear_history();
	return (status);
}*/

void	final_cleanup(t_env *env)
{
	free_env(env);
	rl_clear_history();
}

int	process_user_command(char *input, t_env *env, int *status)
{
	int	exit_flag;

	exit_flag = process_input(input, env, status);
	disable_quit_signal();
	g_signal_received = 0;
	return (exit_flag);
}

int	handle_signal_and_input(char **input, int *status)
{
	if (g_signal_received == SIGINT)
	{
		if (*input)
		{
			free(*input);
			*input = NULL;
		}
		g_signal_received = 0;
		*status = 130;
		return (1);
	}
	return (0);
}

void	initialize_iteration(void)
{
	g_signal_received = 0;
	rl_event_hook = my_event_hook;
	rl_catch_signals = 0;
	setup_signal_handlers();
	disable_quit_signal();
}
