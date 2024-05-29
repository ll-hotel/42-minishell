/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:54:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 14:28:51 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

long	llst_len(t_llst_head *lst)
{
	long	len;

	len = 0;
	if (lst)
		lst = (t_llst_head *)lst->first;
	while (lst)
	{
		len += 1;
		lst = (t_llst_head *)lst->first;
	}
	return (len);
}
