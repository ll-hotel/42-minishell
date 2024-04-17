/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_get_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:15:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/20 17:16:42 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	*llst_get_last(t_llst_head *lst)
{
	t_llst	*element;

	element = lst->first;
	if (element)
		while (element->next)
			element = element->next;
	return (element);
}
