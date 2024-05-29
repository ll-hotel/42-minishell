/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/29 03:37:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(t_command *cmd)
{
	char	*pwd;

	if (cmd->argc > 1)
	{
		write(2, "pwd: too many arguments\n", 25);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd[0] != '\0')
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
