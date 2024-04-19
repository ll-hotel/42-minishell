/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:41:47 by lrichaud          #+#    #+#             */
/*   Updated: 2024/04/18 00:48:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_word(char *args, char **args_array, t_cutter *vars);
static void	worder(char *args, size_t *length, ssize_t *i, int *start);

char	**cutter(char *line)
{
	char		**words;
	ssize_t		i;
	t_cutter	cut_vars;

	words = cutter_init_words(line);
	if (!words)
		return (NULL);
	cut_vars.start_word = -1;
	cut_vars.word_len = 0;
	cut_vars.nb_words = 0;
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			worder(line, &cut_vars.word_len, &i, &cut_vars.start_word);
		else
			new_word(line, words, &cut_vars);
		i++;
	}
	new_word(line, words, &cut_vars);
	free(line);
	return (words);
}

static void	new_word(char *args, char **args_array, t_cutter *vars)
{
	if (vars->word_len > 0)
	{
		args_array[vars->nb_words] = ft_substr(args, \
			vars->start_word, vars->word_len);
		if (!args_array[vars->nb_words])
			return ;
	}
	vars->word_len = 0;
	vars->start_word = -1;
	vars->nb_words++;
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
