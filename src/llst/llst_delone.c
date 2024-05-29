/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_delone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:29:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 15:37:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	llst_delone(t_llst_head *lst, void (*__free)(void *))
{
	t_llst	*tmp;

	if (!lst)
		return ;
	tmp = lst->first;
	if (tmp)
		lst->first = tmp->next;
	if (__free)
		__free(tmp);
}
