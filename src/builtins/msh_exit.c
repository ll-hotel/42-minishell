/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 14:52:50 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_exit(t_msh *msh, int status)
{
	llst_clear(&msh->env_vars, &env_var_free);
	llst_clear(&msh->cmds, &command_free);
	llst_clear(&msh->args, &token_free);
	rl_clear_history();
	exit(status & 0xff);
}

int	exit_error_checker(t_msh *msh, t_command *cmd)
{
	ft_putstr_fd("exit\n", 1);
	if (cmd->argc == 1)
		msh_exit(msh, msh_status_get());
	if (cmd->argc >= 2 && !ft_is_number(cmd->argv[1]))
	{
		ft_dprintf(2, "minishell: exit: numeric argument required\n");
		msh_exit(msh, 2);
	}
	if (cmd->argc == 2)
		msh_exit(msh, ft_atoi(cmd->argv[1]));
	ft_dprintf(2, "minishell: exit: too many arguments\n");
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
