/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:34:44 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 05:43:35 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint8_t	status_storage(int action, uint8_t value)
{
	static uint8_t	status = 0;

	if (action == 1)
		status = value;
	return (status);
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
