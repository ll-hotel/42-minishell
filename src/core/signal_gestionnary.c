/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_gestionnary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:53:57 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/21 16:46:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	reception(int sig);

int	g_signal = 0;

void	signal_gestionnary(void)
{
	g_signal = 0;
	ch_signal(SIGINT, reception);
	ch_signal(SIGQUIT, SIG_IGN);
}

static void	reception(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	ch_status_set(128 + sig);
}
