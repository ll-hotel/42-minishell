/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:54:37 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 23:56:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	handle_quoted(char *cut, int quote);

t_llst	*parse_quotes(char **cuts)
{
	t_llst_head	arg_lst;
	t_token		*arg;
	long		i;
	long		j;

	arg_lst.first = char_array_to_token(cuts);
	free_array((void **)cuts);
	if (!arg_lst.first)
		return (NULL);
	i = 0;
	arg = (void *)arg_lst.first;
	while (arg)
	{
		j = 0;
		while (arg->str[j])
		{
			while (arg->str[j] && !is_quote(arg->str[j]))
				j++;
			if (is_quote(arg->str[j]))
				j += handle_quoted(&(arg->str[j]), arg->str[j]);
		}
		arg = arg->next;
		i++;
	}
	return (arg_lst.first);
}

static long	handle_quoted(char *cut, int quote)
{
	char	*closing_quote;

	closing_quote = ft_strchr(cut + 1, quote);
	if (!closing_quote)
	{
		ft_dprintf(2, "-- ERROR: \"%s\"\n", cut);
		exit(127);
	}
	ft_memmove(closing_quote, closing_quote + 1, ft_strlen(closing_quote));
	ft_memmove(cut, cut + 1, ft_strlen(cut));
	return (closing_quote - cut - 1);
}
