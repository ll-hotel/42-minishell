/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:12:20 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:27:21 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"

void	ft_lstadd_back(t_list **l, t_list *_new)
{
	t_list	*last;

	if (!*l)
	{
		*l = _new;
		return ;
	}
	last = *l;
	while (last->next)
		last = last->next;
	last->next = _new;
}
