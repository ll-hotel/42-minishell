/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:26:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 01:29:37 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static char	*get_shlvl(char *old_value);
static int	loop_body(t_evar *evar_head, t_evar *var);

int	ch_env_init(t_ch *ch, char *const *envp)
{
	t_evar	*var;
	long	i;

	i = 0;
	while (i >= 0 && envp[i])
	{
		var = evar_new(envp[i++]);
		if (!var)
			i = -1;
		else if (!loop_body((t_evar *)&ch->evars, var))
			i = -1;
	}
	if (i == -1)
	{
		llst_clear(&ch->evars, &evar_free);
		return (0);
	}
	return (1);
}

static int	loop_body(t_evar *evar_head, t_evar *var)
{
	if (ft_strcmp(var->name, "SHLVL") == 0)
	{
		var->value = get_shlvl(var->value);
		if (!var->value)
		{
			evar_free(var);
			return (0);
		}
	}
	if (!ch_insert_evar(evar_head, var))
	{
		evar_free(var);
		return (0);
	}
	return (1);
}

static char	*get_shlvl(char *old_value)
{
	char	*tmp;

	if (!old_value || !ft_is_number(old_value))
		tmp = ft_strdup("1");
	else
		tmp = ft_itoa(ft_atoi(old_value) + 1);
	if (old_value)
		free(old_value);
	return (tmp);
}
