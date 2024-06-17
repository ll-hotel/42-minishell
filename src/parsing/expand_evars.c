/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_evars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:52:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/02 23:29:35 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

int	expand_evars(t_token *head, t_ch *ch)
{
	while (head->next)
	{
		if (head->next->type == TOKEN_ENV_VAR)
		{
			if (!evar_expand((t_llst_head *)head, ch))
				return (0);
		}
		if (head->next->type == TOKEN_DQUOTE)
		{
			if (!parse_dquote(head, ch))
				return (0);
		}
		head = head->next;
	}
	return (1);
}
