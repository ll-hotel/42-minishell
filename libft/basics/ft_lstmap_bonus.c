/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:36:01 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:28:05 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

void	go_next(t_list **a, t_list **b)
{
	*a = (*a)->next;
	*b = (*b)->next;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*m;
	t_list	*e;

	if (!lst)
		return (0);
	m = malloc(sizeof(t_list));
	if (!m)
		return (0);
	m->content = f(lst->content);
	e = m;
	while (lst->next)
	{
		e->next = malloc(sizeof(t_list));
		if (!e->next)
			return (ft_lstclear(&m, del), (void *)0);
		go_next(&e, &lst);
		e->content = f(lst->content);
		e->next = 0;
	}
	return (m);
}
