/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:52:04 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/21 14:53:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

int	ch_signal(int sig, void (*hook)(int))
{
	struct sigaction	action;

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_restorer = 0;
	action.sa_sigaction = 0;
	action.sa_handler = hook;
	return (sigaction(sig, &action, 0));
}
