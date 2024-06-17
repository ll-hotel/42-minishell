/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/17 22:03:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static int	insert_evar(t_evar *evar_head, t_evar *evar);
static int	evar_is_valid(char *arg);

int	ch_export(t_cmd *cmd, t_ch *ch)
{
	t_evar	*evar;
	int		i;

	i = 0;
	while (++i < cmd->argc)
	{
		evar = evar_new(cmd->argv[i]);
		if (!evar)
			perror("export");
		else if (!evar_is_valid(evar->name))
		{
			ft_dprintf(2, "export: %s: not a valid identifier\n", evar->name);
			evar_free(evar);
			return (1);
		}
		else if (evar->value && !insert_evar((t_evar *)&ch->evars, evar))
		{
			perror("export");
			return (1);
		}
		else
			evar_free(evar);
	}
	return (0);
}

static int	insert_evar(t_evar *evar_head, t_evar *evar)
{
	const int	length = ft_strlen(evar->name) + 1;

	while (evar_head->next && \
			ft_strncmp(evar_head->next->name, evar->name, length))
	{
		evar_head = evar_head->next;
	}
	if (!evar_head->next)
		evar_head->next = evar;
	else if (evar->value)
	{
		ft_free(evar_head->next->value);
		evar_head->next->value = ft_strdup(evar->value);
		if (!evar_head->next->value)
			return (perror("miniChell"), 0);
	}
	else
		return (0);
	return (1);
}

static int	evar_is_valid(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (ft_isalnum(arg[i]))
		i++;
	if (arg[i])
		return (0);
	return (1);
}
