/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 06:51:48 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/20 00:40:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static int	insert_evar(t_evar *evar_head, t_evar *evar);
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
		else if (!insert_evar((t_evar *)&ch->evars, evar))
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
