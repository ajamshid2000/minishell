/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajamshid <ajamshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/17 16:54:43 by ajamshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

char	*allocate_heredoc_content(void)
{
	char	*heredoc_content;

	heredoc_content = malloc(1);
	if (heredoc_content == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	heredoc_content[0] = '\0';
	return (heredoc_content);
}

int	read_from_pipe(int pipe_read_fd, char *buffer, size_t buffer_size)
{
	int	bytes_read;

	bytes_read = read(pipe_read_fd, buffer, buffer_size - 1);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

char	*resize_and_append(char *heredoc_content, const char *buffer,
		size_t *total_length, int bytes_read)
{
	size_t	new_length;
	char	*new_content;

	new_length = *total_length + bytes_read + 1;
	new_content = my_realloc(heredoc_content, new_length, *total_length + 1);
	if (new_content == NULL)
	{
		free(heredoc_content);
		perror("my_realloc");
		return (NULL);
	}
	heredoc_content = new_content;
	my_strcpy(heredoc_content + *total_length, buffer);
	*total_length += bytes_read;
	return (heredoc_content);
}

/*
char	*read_heredoc_content(int pipe_read_fd)
{
	char	buffer[1024];
	int		bytes_read;
	size_t	total_length;
	char	*heredoc_content;

	heredoc_content = allocate_heredoc_content();
	total_length = 0;
	if (heredoc_content == NULL)
		return (NULL);
	while ((bytes_read = read_from_pipe(pipe_read_fd, buffer,
				sizeof(buffer))) > 0)
	{
		heredoc_content = resize_and_append(heredoc_content, buffer,
				&total_length, bytes_read);
		if (heredoc_content == NULL)
			return (NULL);
	}
	return (heredoc_content);
}
*/
char	*read_heredoc_content(int pipe_read_fd)
{
	char	buffer[1024];
	int		bytes_read;
	size_t	total_length;
	char	*heredoc_content;

	heredoc_content = allocate_heredoc_content();
	return (heredoc_content);
	total_length = 0;
	if (heredoc_content == NULL)
		return (NULL);
	bytes_read = read_from_pipe(pipe_read_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		heredoc_content = resize_and_append(heredoc_content, buffer,
				&total_length, bytes_read);
		if (heredoc_content == NULL)
			return (NULL);
		bytes_read = read_from_pipe(pipe_read_fd, buffer, sizeof(buffer));
	}
	return (heredoc_content);
}
