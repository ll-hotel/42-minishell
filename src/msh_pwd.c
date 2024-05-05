/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/22 20:14:02 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_command *cmd)
{
	char	*buff;
	size_t	size;

	if (cmd->argc > 1)
	{
		write(2, "pwd : too many arguments\n", 25);
		return (1);
	}
	size = 128;
	buff = ft_calloc(size, sizeof(char));
	if (!buff)
		return (1);
	while (!getcwd(buff, size) && size < __INT_MAX__)
	{
		free(buff);
		size *= 2;
		buff = ft_calloc(size, sizeof(char));
		if (!buff)
			return (1);
	}
	if (buff[0] != '\0')
		printf("%s\n", buff);
	free(buff);
	return (0);
}
