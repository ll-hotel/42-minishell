/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:38:07 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/23 16:34:51 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	is_param(char *str);

int	ch_echo(t_cmd *cmd)
{
	char	backslash;
	int		i;

	backslash = '\n';
	i = 1;
	while (i < cmd->argc && is_param(cmd->argv[i]))
		i += 1;
	if (i > 1)
		backslash = 0;
	while (i < cmd->argc)
	{
		printf("%s", cmd->argv[i]);
		if (i + 1 < cmd->argc)
			printf(" ");
		i += 1;
	}
	printf("%c", backslash);
	return (0);
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
		if (!str[i])
			return (i);
	}
	return (0);
}
