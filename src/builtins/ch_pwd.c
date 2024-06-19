/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/17 22:04:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

int	ch_pwd(t_ch *ch)
{
	char	*pwd;
	t_evar	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		oldpwd = find_evar(ch, "OLDPWD");
		if (oldpwd && oldpwd->value)
			printf("%s\n", oldpwd->value);
	}
	return (0);
}
