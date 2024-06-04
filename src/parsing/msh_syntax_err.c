/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_syntax_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:38:12 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/03 03:29:36 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_syntax_err(char c)
{
	if (c > 0)
		ft_dprintf(2, "minishell: syntax error near " \
				"unexpected token `%c'\n", c);
	else if (c < 0)
	{
		ft_dprintf(2, \
			"minishell: unexpected EOF while looking for matching `%c'\n", -c);
	}
	if (!c || c == - '\'' || c == - '\"')
		ft_dprintf(2, "minishell: syntax error: unexpected end of file\n");
}
