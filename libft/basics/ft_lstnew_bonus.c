/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:12:09 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:27:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = malloc(sizeof(*l));
	if (!l)
		return (0);
	l->content = content;
	l->next = 0;
	return (l);
}
