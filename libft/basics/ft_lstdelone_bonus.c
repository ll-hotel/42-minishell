/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:36:11 by ll-hotel          #+#    #+#             */
/*   Updated: 2023/12/07 19:28:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	if (lst->content)
		f(lst->content);
	lst->content = 0;
	free(lst);
}
