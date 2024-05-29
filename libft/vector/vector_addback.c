/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:26:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 19:01:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*ft_realloc(void *p, uint64_t size, uint64_t new_size);
void	*ft_memmove(void *dest, void *src, uint64_t size);

void	*vec_addback(t_vec *vec, void *elem)
{
	void	*tmp;

	if (vec->size >= vec->allocated_size)
	{
		vec->allocated_size = vec->size + 1;
		vec->allocated_size *= 2;
		tmp = ft_realloc(vec->array, \
				vec->size * vec->elem_size, \
				vec->allocated_size * vec->elem_size);
		if (!tmp)
			return (0);
		vec->array = tmp;
	}
	vec->size += 1;
	if (vec->elem_size > sizeof(uint64_t))
		ft_memmove(vec_at(vec, vec->size -1), elem, vec->elem_size);
	else
		ft_memmove(vec_at(vec, vec->size -1), &elem, vec->elem_size);
	return (vec_at(vec, vec->size -1));
}
