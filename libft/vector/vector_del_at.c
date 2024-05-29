/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_del_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:32:25 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 19:09:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basics.h"
#include "vector.h"

void	vec_del_at(t_vec *vec, uint64_t i, void (*__free)(void *))
{
	void	*p_elt;

	p_elt = vec_at(vec, i);
	if (!p_elt)
		return ;
	if (__free)
		__free(p_elt);
	ft_memmove(p_elt, \
			p_elt + vec->elem_size, \
			vec->elem_size * (vec->size - i - 1));
	vec->size -= 1;
	if (vec->size)
		ft_bzero(vec_at(vec, vec->size - 1), vec->elem_size);
}
