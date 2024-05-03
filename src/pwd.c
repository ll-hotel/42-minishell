/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/03 20:07:31 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_checker(void *ptr)
{
	if (!ptr)
	{
		perror("Malloc failed");
		exit(1);
	}
}



void	pwd(void)
{
	char	*buff;
	size_t	size;

	size = 128;
	buff = ft_calloc(size, sizeof(char));
	malloc_checker(buff);
	while (!getcwd(buff, size) && size < __INT_MAX__)
	{
		free(buff);
		size *= 2;
		buff = ft_calloc(size, sizeof(char));
		malloc_checker(buff);
	}
	if (buff[0] != '\0')
		printf("%s\n", buff);
	free(buff);
}
