/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/29 03:56:21 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(void)
{
	char	*buff;
	size_t	size;

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

char	*pwd_prompt(void)
{
	char	*buff;
	size_t	size;
	char	*temp;

	size = 128;
	buff = ft_calloc(size, sizeof(char));
	if (!buff)
		return (NULL);
	while (!getcwd(buff, size) && size < __INT_MAX__)
	{
		free(buff);
		size *= 2;
		buff = ft_calloc(size, sizeof(char));
		if (!buff)
			return (NULL);
	}
	temp = ft_strjoin("\001\e[96m\e[1m\002📂 ", ft_strrchr(buff, '/'));
	free(buff);
	buff = ft_strjoin(temp, "\001\e[0m\e[39m\002 ➡️ ");
	free(temp);
	return (buff);
}
