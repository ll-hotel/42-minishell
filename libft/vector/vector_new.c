/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:24:34 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/16 16:37:21 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vec_new(t_vec *vec, unsigned long elem_size)
{
	if (vec == (void *)0 || elem_size == 0)
		return ;
	vec->elem_size = elem_size;
	vec->array = (void *)0;
	vec->size = 0;
	vec->allocated_size = 0;
}
