/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:30:43 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 06:41:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_exit(t_msh *msh, int status)
{
	llst_clear(&msh->env_vars, &env_var_free);
	llst_clear(&msh->cmds, &command_free);
	llst_clear(&msh->args, &token_free);
	vec_clear(&msh->children, NULL);
	exit(status);
}
