/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_addback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:46:00 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 19:52:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	llst_addback(t_llst_head *lst, t_llst *element)
{
	t_llst	*tmp;

	tmp = (void *)lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
}
