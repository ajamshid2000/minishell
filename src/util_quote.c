/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: famana <famana@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:39 by ajamshid          #+#    #+#             */
/*   Updated: 2024/10/16 10:26:52 by famana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/* Helper function to check if a character at index i is escaped*/
int	is_escaped(char *string, size_t i)
{
	int	escape;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	escape = 0;
	while (i > 0 && string[i - 1] == '\\')
	{
		escape = !escape;
		i--;
	}
	return (escape);
}

/* Helper function to check if a character at index i is inside double quotes */
int	is_in_double_quote(char *string, size_t i)
{
	int		in_double_quote;
	int		in_single_quote;
	size_t	j;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	in_double_quote = 0;
	in_single_quote = 0;
	j = 0;
	while (j < i)
	{
		if (!is_escaped(string, j))
		{
			if (string[j] == '\"' && !in_single_quote)
				in_double_quote = !in_double_quote;
			else if (string[j] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
		}
		j++;
	}
	return (in_double_quote);
}

/* Helper function to check if a character at index i is inside single quotes */
int	is_in_quote_simple(char *string, size_t i)
{
	int		in_double_quote;
	int		in_single_quote;
	size_t	j;

	if (string == NULL || i >= ft_strlen(string))
		return (0);
	in_double_quote = 0;
	in_single_quote = 0;
	j = 0;
	while (j < i)
	{
		if (!is_escaped(string, j))
		{
			if (string[j] == '\"' && !in_single_quote)
			{
				in_double_quote = !in_double_quote;
			}
			else if (string[j] == '\'' && !in_double_quote)
			{
				in_single_quote = !in_single_quote;
			}
		}
		j++;
	}
	return (in_single_quote);
}

int	is_quote_escaped(char *string, size_t i)
{
	return ((is_in_quote_simple(string, i) == 1 || is_in_double_quote(string,
				i) == 1 || is_escaped(string, i) == 1));
}

/* Function to check for unclosed quotes in a string */
int	has_unclosed_quotes(const char *string)
{
	int		in_single_quote;
	int		in_double_quote;
	size_t	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	if (string == NULL)
		return (0);
	while (string[i] != '\0')
	{
		if (!is_escaped((char *)string, i))
		{
			if (string[i] == '\'' && !in_double_quote)
				in_single_quote = !in_single_quote;
			else if (string[i] == '\"' && !in_single_quote)
				in_double_quote = !in_double_quote;
		}
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (1);
	else
		return (0);
}
