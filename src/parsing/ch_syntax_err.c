/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_syntax_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:38:12 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 11:19:07 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

void	ch_syntax_err(char c)
{
	if (c > 0)
		ft_dprintf(2, "miniChell: syntax error near " \
				"unexpected token `%c'\n", c);
	else if (c < 0)
	{
		ft_dprintf(2, \
			"miniChell: unexpected EOF while looking for matching `%c'\n", -c);
	}
	if (c == - '\'' || c == - '\"')
		ft_dprintf(2, "miniChell: syntax error: unexpected end of file\n");
	else if (!c)
		ft_dprintf(2, "miniChell: syntax error " \
				"near unexpected token `newline'\n");
	ch_status_set(2);
}
