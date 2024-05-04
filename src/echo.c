/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:38:07 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/04 12:47:42 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	param(char *str, char **printed, char *backslash);
static int	is_param(char *str);

void	echo(char *command)
{
	char	backslash;
	char	*printed;

	printed = "";
	backslash = '\n';
	param(command, &printed, &backslash);
	while (is_param(printed))
		param(printed, &printed, &backslash);
	printf("%s%c", printed, backslash);
}

static void	param(char *str, char **printed, char *backslash)
{
	char	*new_start;

	new_start = ft_strnstr(str, "-n", 7);
	if (new_start)
	{
		*printed = new_start;
		*printed += is_param(*printed);
		*backslash = '\n' * (!is_space(**printed) && **printed);
		*printed += is_space(**printed);
	}
	else if (is_space(str[4]))
		*printed = str + 5;
}

static int	is_param(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (is_space(str[i]) || !str[i])
			return (i);
	}
	return (0);
}
