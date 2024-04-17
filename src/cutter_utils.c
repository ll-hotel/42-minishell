/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:03 by lrichaud          #+#    #+#             */
/*   Updated: 2024/04/18 00:57:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	words_counter(char *line);

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	**cutter_init_words(char *line)
{
	int		nb_args;
	char	**array_ptr;

	nb_args = words_counter(line);
	if (nb_args <= 0)
		return (NULL);
	array_ptr = ft_calloc(nb_args + 1, sizeof(char *));
	if (!array_ptr)
		return (NULL);
	return (array_ptr);
}

static int	words_counter(char *line)
{
	ssize_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!line[0])
		return (0);
	if (!is_space(line[0]))
		count++;
	if (is_quote(line[0]))
		i = quote_reader(line, i, line[i]);
	if (i == -1)
		return (-1);
	while (line[++i])
	{
		if (!is_space(line[i]) && is_space(line[i - 1]))
			count++;
		if (is_quote(line[i]))
		{
			i = quote_reader(line, i, line[i]);
			if (i == -1)
				return (-1);
		}
	}
	return (count);
}

size_t	quote_reader(char *line, ssize_t i, char quote_type)
{
	i++;
	while (line[i] && line[i] != quote_type)
		i = i + 1;
	if (line[i] == quote_type)
		return (i);
	ft_dprintf(2, "Quote error\n");
	return (-1);
}

