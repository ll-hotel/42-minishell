/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:21:03 by lrichaud          #+#    #+#             */
/*   Updated: 2024/04/17 13:10:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

char	**init_args_array(char *args)
{
	int		nb_args;
	char	**array_ptr;

	nb_args = args_counter(args);
	if (nb_args <= 0)
		return (NULL);
	array_ptr = ft_calloc(nb_args + 1, sizeof(char *));
	if (!array_ptr)
		return (NULL);
	return (array_ptr);
}
