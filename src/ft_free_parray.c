/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/22 14:19:16 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_parray(void *array)
{
	void	**p;

	if (array)
	{
		p = array;
		if (p)
			while (*p)
				free(*(p++));
		free(array);
	}
}
