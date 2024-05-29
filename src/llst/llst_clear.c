/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:53:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 16:07:47 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	llst_clear(t_llst_head *lst, void (*__free)(void *))
{
	if (!lst)
		return ;
	while (lst->first)
		llst_delone(lst, __free);
}
