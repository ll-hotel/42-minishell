/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:53:49 by ll-hotel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/27 16:07:47 by ll-hotel         ###   ########.fr       */
=======
/*   Updated: 2024/04/17 22:42:10 by ll-hotel         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"
#include <stdlib.h>

void	llst_clear(t_llst_head *lst, void (*__free)(void *))
{
<<<<<<< HEAD
	if (!lst)
		return ;
	while (lst->first)
		llst_delone(lst, __free);
=======
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
>>>>>>> main
}
