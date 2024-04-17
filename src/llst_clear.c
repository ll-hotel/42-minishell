/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:53:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 22:42:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"
#include <stdlib.h>

void	llst_clear(t_llst_head *lst, void (*f)(void *))
{
	t_llst	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		lst->first = tmp->next;
		f(tmp);
		free(tmp);
		tmp = lst->first;
	}
	lst->first = NULL;
}
