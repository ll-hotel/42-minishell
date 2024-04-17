/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:53:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 20:23:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	llst_clear(t_llst_head *lst, void (*f)(void *))
{
	t_llst	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		lst->first = tmp->next;
		f(tmp);
		tmp = lst->first;
	}
}
