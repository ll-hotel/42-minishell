/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:38:07 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/23 20:48:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	is_param(char *str);

int	ch_echo(t_cmd *cmd)
{
	char	backslash[2];
	int		i;

	backslash[0] = '\n';
	backslash[1] = 0;
	i = 1;
	while (i < cmd->argc && is_param(cmd->argv[i]))
		i += 1;
	if (i > 1)
		*backslash = 0;
	while (i < cmd->argc)
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (i + 1 < cmd->argc)
			ft_putstr_fd(" ", 1);
		i += 1;
	}
	ft_putstr_fd(backslash, 1);
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
