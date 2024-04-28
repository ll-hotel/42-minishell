/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:12:29 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:28:36 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

void	ft_lstadd_front(t_list **l, t_list *_new)
{
	t_list	*e;

	e = _new;
	if (!e)
		return ;
	while (e->next)
		e = e->next;
	e->next = (*l);
	(*l) = _new;
}
