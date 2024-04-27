/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:54:21 by ll-hotel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/27 18:15:43 by ll-hotel         ###   ########.fr       */
=======
/*   Updated: 2024/04/18 00:05:54 by ll-hotel         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_array(void **ptr)
{
<<<<<<< HEAD
	void *const	p = ptr;
=======
	void	*const p = ptr;
>>>>>>> main

	if (ptr)
	{
		while (*ptr)
			free(*(ptr++));
		free(p);
	}
}
