/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:36:05 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 19:07:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "basics.h"
#include <stdlib.h>

void	vec_clear(t_vec *vec, void (*del)(void *))
{
	uint64_t	i;

	if (vec->array)
	{
		if (del)
		{
			i = 0;
			while (i < vec->size)
				del(vec_at(vec, i++));
		}
		ft_bzero(vec->array, vec->allocated_size * vec->elem_size);
		free(vec->array);
	}
	vec->array = (void *)0;
	vec->size = 0;
	vec->allocated_size = 0;
	vec->elem_size = 0;
}
