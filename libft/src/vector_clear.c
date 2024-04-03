/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:36:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/01 14:17:30 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

void	vec_clear(t_vec *vec, void (*del)(void *))
{
	uint64_t	i;

	if (vec->array)
	{
		if (del)
		{
			i = -1;
			while (++i < vec->size)
				(*del)(*(void **)vec_at(vec, i));
		}
		ft_memset(vec->array, 0, vec->size * vec->elem_size);
		free(vec->array);
	}
	vec->array = (void *)0;
	vec->size = 0;
	vec->allocated_size = 0;
	vec->elem_size = 0;
}
