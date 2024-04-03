/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:52:27 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/03/17 16:24:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *p, uint64_t old_size, uint64_t n)
{
	void	*new;

	if (n == 0)
		return (NULL);
	new = malloc(n);
	if (!new)
		return (NULL);
	if (!p)
		return (new);
	if (n < old_size)
		ft_memmove(new, p, n);
	else
		(void)ft_memmove(new, p, old_size);
	return (free(p), new);
}
