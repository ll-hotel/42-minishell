/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:41:47 by lrichaud          #+#    #+#             */
/*   Updated: 2024/04/17 23:53:26 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	quote_reader(char *str, ssize_t i, char quote_type);
static int		new_word(char *args, char **args_array, t_cutter *vars);
static void		worder(char *args, size_t *length, ssize_t *i, int *start);

int	args_counter(char *str)
{
	ssize_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!str[0])
		return (0);
	if (!is_space(str[0]))
		count++;
	if (is_quote(str[0]))
		i = quote_reader(str, i, str[i]);
	if (i == -1)
		return (-1);
	while (str[++i])
	{
		if (!is_space(str[i]) && is_space(str[i - 1]))
			count++;
		if (is_quote(str[i]))
		{
			i = quote_reader(str, i, str[i]);
			if (i == -1)
				return (-1);
		}
	}
	return (count);
}

char	**cutter(char *args)
{
	char		**args_array;
	ssize_t		i;
	t_cutter	cut_vars;

	i = 0;
	cut_vars.start_word = -1;
	cut_vars.word_len = 0;
	args_array = init_args_array(args);
	if (!args_array)
		return (NULL);
	cut_vars.nb_args = 0;
	while (args[i])
	{
		if (!is_space(args[i]))
			worder(args, &cut_vars.word_len, &i, &cut_vars.start_word);
		else
			new_word(args, args_array, &cut_vars);
		i++;
	}
	new_word(args, args_array, &cut_vars);
	free(args);
	return (args_array);
}

static size_t	quote_reader(char *str, ssize_t i, char quote_type)
{
	i++;
	while (str[i] && str[i] != quote_type)
		i = i + 1;
	if (str[i] == quote_type)
		return (i);
	printf("Quote error\n");
	return (-1);
}

static int	new_word(char *args, char **args_array, t_cutter *vars)
{
	if (vars->word_len > 0)
	{
		args_array[vars->nb_args] = ft_substr(args, \
			vars->start_word, vars->word_len);
		if (!args_array[vars->nb_args])
			return (0);
	}
	vars->word_len = 0;
	vars->start_word = -1;
	vars->nb_args++;
	return (1);
}

static void	worder(char *args, size_t *word_len, ssize_t *i, int *start_index)
{
	char	temp;

	if (*start_index == -1)
		*start_index = *i;
	if (is_quote(args[*i]))
	{
		temp = args[*i];
		while (args[++(*i)] && args[*i] != temp)
			*word_len += 1;
		*word_len += 1;
	}
	*word_len += 1;
}
