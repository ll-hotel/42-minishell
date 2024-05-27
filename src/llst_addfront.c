/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst_addfront.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:45:03 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/27 19:36:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "llst.h"

void	llst_addfront(t_llst_head *lst, t_llst *element)
{
	element->next = lst->first;
	lst->first = element;
}
