/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_gestionnary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:53:57 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/11 19:04:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	reception(int sig);

void	signal_gestionnary(void)
{
	signal(SIGINT, reception);
	signal(SIGQUIT, SIG_IGN);
}

static void	reception(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ch_status_set(130);
	}
}
