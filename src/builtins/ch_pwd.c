/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:05:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 16:45:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

int	ch_pwd(t_ch *ch)
{
	char	*pwd;
	t_evar	*oldpwd;

	pwd = get_pwd(ch);
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
		else
			printf("CPT\n");
	}
	return (0);
}

char	*get_pwd(t_ch *ch)
{
	t_evar		*evar_pwd;

	evar_pwd = find_evar(ch, "PWD");
	if (evar_pwd)
		return (ft_strdup(evar_pwd->value));
	else
		return (getcwd(NULL, 0));
}
