/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:34:44 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/03 06:17:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint8_t	status_storage(int action, uint8_t value)
{
	static uint16_t	status = 0;

	if (action == 1)
	{
		if (value)
			status = ((uint16_t)value << 8) | value;
		else
			status = (status & 0xff00) | value;
	}
	else if (action == 2)
		return (status >> 8);
	return (status & 0xff);
}

uint8_t	msh_status_set(uint8_t value)
{
	status_storage(1, value);
	return (value);
}

uint8_t	msh_status_get(void)
{
	return (status_storage(0, 0));
}

uint8_t	msh_status_get_error(void)
{
	return (status_storage(2, 0));
}
