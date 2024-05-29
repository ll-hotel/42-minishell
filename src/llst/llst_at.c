/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:22:04 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 12:23:41 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

t_llst	*llst_at(t_llst_head *lst_head, int i)
{
	t_llst	*lst_elt;

	lst_elt = lst_head->first;
	while (i-- > 0 && lst_elt)
		lst_elt = lst_elt->next;
	return (lst_elt);
}
