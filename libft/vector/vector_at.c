/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:32:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/16 16:37:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*vec_at(t_vec *vec, unsigned long i)
{
	if (i > vec->size || !vec->array)
		return (0);
	return (vec->array + i * vec->elem_size);
}
