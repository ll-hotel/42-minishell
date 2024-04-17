/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:54:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 22:55:49 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

long	llst_len(t_llst_head *lst)
{
	t_llst	*tmp;
	long	len;

	len = 0;
	tmp = lst->first;
	while (tmp)
	{
		len += 1;
		tmp = tmp->next;
	}
	return (len);
}
