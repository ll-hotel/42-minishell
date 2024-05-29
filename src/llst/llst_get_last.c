/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_get_last.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:15:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/10 23:50:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

t_llst	*llst_get_last(t_llst_head *lst)
{
	t_llst	*element;

	element = lst->first;
	if (element)
		while (element->next)
			element = element->next;
	return (element);
}
