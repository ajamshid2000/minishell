/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:24:10 by ajamshid          #+#    #+#             */
/*   Updated: 2024/08/20 19:23:36 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (len == 0)
		return (len);
	i = 0;
	while (i < (len - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	print_n(char **command, int out_fd, t_commands *commands)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!ft_strcmp(command[i], "$?"))
			ft_putstr_fd(ft_itoa(commands->status), out_fd);
		else if (ft_strcmp(command[i], "-n"))
			ft_putstr_fd(command[i], out_fd);
		i++;
	}
	return (0);
}

int	print(char **command, int out_fd, t_commands *commands)
{
	int		i;
	char	*temp;

	i = 0;
	if (!command[i])
		ft_putstr_fd("\n", out_fd);
	while (command[i])
	{
		if (!ft_strcmp(command[i], "$?"))
			temp = ft_strjoin(ft_itoa(commands->status), "\n");
		else
			temp = ft_strjoin(command[i], "\n");
		ft_putstr_fd(temp, out_fd);
		free(temp);
		i++;
	}
	return (0);
}

int	echo(char **command, int out_fd, t_commands *commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		if (!ft_strcmp(command[i], "-n"))
			j = 1;
		i++;
	}
	if (j == 1)
		print_n(command, out_fd, commands);
	if (j != 1)
		print(command, out_fd, commands);
	return (0);
}
