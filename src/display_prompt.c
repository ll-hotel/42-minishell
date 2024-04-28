/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:17:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/28 08:13:42 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	is_only_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

char	*display_prompt(void)
{
	char	*input;

	input = readline("[\001\e[96m\e[1m\002miniChell\001\e[0m\e[39m\002]-$ ");
	if (input && !is_only_space(input))
	{
		add_history(input);
		return (input);
	}
	return (NULL);
}
