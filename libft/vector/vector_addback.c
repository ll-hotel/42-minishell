/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:26:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/02 14:18:59 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*ft_realloc(void *p, unsigned long old_size, unsigned long n);
void	*ft_memmove(void *p1, void *p2, unsigned long n);
void	ft_bzero(void *p, unsigned long size);

void	*vec_addback(t_vec *vec, void *elem)
{
	void	*tmp;

	if (vec->size >= vec->allocated_size)
	{
		vec->allocated_size += 1;
		vec->allocated_size *= 1.5;
		tmp = ft_realloc(vec->array, vec->size * vec->elem_size, \
				vec->allocated_size * vec->elem_size);
		if (!tmp)
			return (0);
		ft_bzero(tmp + vec->size * vec->elem_size, \
				(vec->allocated_size - vec->size) * vec->elem_size);
		vec->array = tmp;
	}
	if (vec->elem_size > 8)
		ft_memmove(vec_at(vec, vec->size), elem, vec->elem_size);
	else
		ft_memmove(vec_at(vec, vec->size), &elem, vec->elem_size);
	return (vec_at(vec, (vec->size)++));
}
