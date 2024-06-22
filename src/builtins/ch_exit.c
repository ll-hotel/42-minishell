/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 14:52:50 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

void	ch_exit(t_ch *ch, int status)
{
	llst_clear(&ch->evars, &evar_free);
	llst_clear(&ch->cmds, &cmd_free);
	llst_clear(&ch->args, &token_free);
	rl_clear_history();
	exit(status & 0xff);
}

int	exit_error_checker(t_ch *ch, t_cmd *cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd->argc == 1)
		ch_exit(ch, ch_status_get());
	if (cmd->argc >= 2 && !ft_is_number(cmd->argv[1]))
	{
		ft_dprintf(2, "miniChell: exit: numeric argument required\n");
		ch_exit(ch, 2);
	}
	if (cmd->argc == 2)
		ch_exit(ch, ft_atoi(cmd->argv[1]));
	ft_dprintf(2, "miniChell: exit: too many arguments\n");
	return (1);
}

int	ft_is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '\0')
			return (0);
		if (!ft_isdigit(str[i]))
		{
			if (str[i] != '-' && str[i] != '+')
				return (0);
			if (str[i + 1] == '\0')
				return (0);
			if (i >= 1 && str[i - 1] != ' ')
				return (0);
		}
		i++;
	}
	return (1);
}
