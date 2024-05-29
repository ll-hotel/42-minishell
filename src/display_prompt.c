/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:17:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 07:45:19 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	is_only_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

char	*display_prompt(void)
{
	char	*input;
	char	*prompt;

	prompt = pwd_prompt();
	input = readline(prompt);
	free(prompt);
	if (input && !is_only_space(input))
	{
		add_history(input);
		return (input);
	}
	return (input);
}
