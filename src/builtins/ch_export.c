/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/24 10:48:15 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"
#include "minichell.h"

static int	export_one(t_ch *ch, char *arg);
static int	evar_is_valid(char *arg);
static void	printer(t_ch *ch);

int	ch_export(t_cmd *cmd, t_ch *ch)
{
	int		i;
	int		error;

	if (cmd->argc == 1)
		return (printer(ch), 0);
	error = 0;
	i = 0;
	while (++i < cmd->argc)
	{
		error |= export_one(ch, cmd->argv[i]);
	}
	return (error);
}

static int	export_one(t_ch *ch, char *arg)
{
	t_evar	*evar;

	evar = evar_new(arg);
	if (!evar)
	{
		perror("export");
		return (1);
	}
	else if (!evar_is_valid(evar->name))
	{
		ft_dprintf(2, "export: %s: not a valid identifier\n", evar->name);
		evar_free(evar);
		return (1);
	}
	ch_insert_evar((t_evar *)&ch->evars, evar);
	return (0);
}

static void	printer(t_ch *ch)
{
	t_evar	*evar;

	evar = (t_evar *) ch->evars.first;
	while (evar && evar->name)
	{
		printf("declare -x %s", evar->name);
		if (evar->value)
			printf("=\"%s\"", evar->value);
		printf("\n");
		evar = evar->next;
	}
}

void	ch_insert_evar(t_evar *evar_head, t_evar *evar)
{
	while (evar_head->next && \
			ft_strcmp(evar_head->next->name, evar->name) < 0)
	{
		evar_head = evar_head->next;
	}
	if (!evar_head->next || ft_strcmp(evar_head->next->name, evar->name) > 0)
		llst_addfront((t_llst_head *)evar_head, (t_llst *)evar);
	else if (evar->value)
	{
		llst_delone((t_llst_head *)evar_head, evar_free);
		llst_addfront((t_llst_head *)evar_head, (t_llst *)evar);
	}
	else
		evar_free(evar);
}

static int	evar_is_valid(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i])
		return (0);
	return (1);
}
