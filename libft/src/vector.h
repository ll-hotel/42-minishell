/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:24:46 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/01 15:24:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "basics.h"

typedef struct s_vector	t_vec;

struct	s_vector
{
	void		*array;
	uint64_t	size;
	uint64_t	elem_size;
	uint64_t	allocated_size;
};

void	vec_new(t_vec *vec, uint64_t elem_size);
void	*vec_addback(t_vec *vec, void *elem);
void	*vec_at(t_vec *vec, uint64_t i);
void	vec_clear(t_vec *vec, void (*del)(void *));

#endif
