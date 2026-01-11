/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:02:24 by abdul-rashe       #+#    #+#             */
/*   Updated: 2024/10/17 17:54:02 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		if (i == 0)
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '+' || str[i] == '-')
				i++;
		}
		if (!ft_isdigit(str[i]))
			return (1);
	}
	if (i > 0 && (str[i - 1] == '+' || str[i - 1] == ' '))
		if (ft_strcmp(&str[i], "9223372036854775807") > 0)
			return (1);
	if (i > 0 && str[i - 1] == '-')
		if (ft_strcmp(&str[i], "9223372036854775808") > 0)
			return (1);
	return (0);
}

long long int	ft_atoi_long(char *nptr)
{
	int				i;
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	if (i != 0 && nptr[i - 1] == '-')
		if (ft_strcmp(&nptr[i], "9223372036854775808") == 0)
			return (LLONG_MIN);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}

void	exit_error(t_commands *commands, int i)
{
	ft_putendl_fd("Exit", 2);
	if (i == 0)
	{
		ft_putstr_fd("minishell: Exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
	}
	if (i == 1)
	{
		ft_putstr_fd("minishell: Exit: ", 2);
		ft_putstr_fd(commands->fcommand[i - 1]->command[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
}

int	exit_minishell(t_commands *commands, int i)
{
	if (commands->fcommand[i - 1]->command[1])
	{
		if (commands->fcommand[i - 1]->command[2]
			&& !ft_isnumeric(commands->fcommand[i - 1]->command[1]))
		{
			exit_error(commands, 0);
			commands->status = 1;
			return (0);
		}
		else if (ft_isnumeric(commands->fcommand[i - 1]->command[1]))
		{
			exit_error(commands, 1);
			commands->status = 2;
			return (1);
		}
		commands->status = (ft_atoi_long(commands->fcommand[i - 1]->command[1])
				% 256);
		ft_putendl_fd("Exit", 2);
		return (1);
	}
	commands->status = 0;
	return (1);
}
