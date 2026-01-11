/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:27:49 by famana            #+#    #+#             */
/*   Updated: 2024/10/17 16:55:30 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

int	main(void)
{
	t_env	*env;
	int		status;
	int		exit_flag;
	char	*input;

	env = create_env_stack();
	status = 0;
	exit_flag = 0;
	rl_event_hook = my_event_hook;
	while (1)
	{
		initialize_iteration();
		input = readline("minishell> ");
		if (handle_signal_and_input(&input, &status))
			continue ;
		if (input == NULL)
			break ;
		exit_flag = process_user_command(input, env, &status);
		if (exit_flag == 1)
			break ;
	}
	if (exit_flag != 1)
		ft_putendl_fd("Exit", 2);
	final_cleanup(env);
	return (status);
}
