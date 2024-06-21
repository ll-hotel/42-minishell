/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 01:30:46 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"
#include "minichell.h"

static int	evar_is_valid(char *arg);
void		printer(t_ch *ch);

int	ch_export(t_cmd *cmd, t_ch *ch)
{
	t_evar	*evar;
	int		i;

	if (cmd->argc == 1)
		return (printer(ch), 0);
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
		else if (!ch_insert_evar((t_evar *)&ch->evars, evar))
		{
			evar_free(evar);
			perror("export");
			return (1);
		}
	}
	return (0);
}

void	printer(t_ch *ch)
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

int	ch_insert_evar(t_evar *evar_head, t_evar *evar)
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
		ft_free(evar_head->next->value);
		evar_head->next->value = ft_strdup(evar->value);
		if (!evar_head->next->value)
			return (perror("miniChell"), 0);
	}
	return (1);
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
