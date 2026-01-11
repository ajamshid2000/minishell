/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/18 13:06:21 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Function to reallocate memory when needed */
char	*reallocate_content(char *content, size_t *capacity, size_t new_size)
{
	char	*new_content;
	size_t	old_size;

	if (new_size >= *capacity)
	{
		old_size = *capacity;
		*capacity *= 2;
		new_content = my_realloc(content, *capacity, old_size);
		if (!new_content)
		{
			free(content);
			return (NULL);
		}
		return (new_content);
	}
	return (content);
}

/* Function to append the line to the content */
void	append_line_to_content(char *content, const char *line,
		size_t *content_size)
{
	ft_strcat(content, line);
	ft_strcat(content, "\n");
	*content_size += ft_strlen(line) + 1;
}

/* Function to process a single line and update the content */
int	process_line(char **content, size_t *content_size, size_t *content_capacity,
		const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	*content = reallocate_content(*content, content_capacity, *content_size
			+ len + 2);
	if (!(*content))
	{
		return (0);
	}
	append_line_to_content(*content, line, content_size);
	return (1);
}

// Main function to handle heredoc and return content + execution flag
char	*handle_heredoc2(const char *stop_word, int *exec_flag, int *here_fd)
{
	char	*heredoc_content;

	heredoc_content = NULL;
	execute_heredoc((char *)stop_word, &heredoc_content, exec_flag, here_fd);
	return (heredoc_content);
}
