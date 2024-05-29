/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_gestionnary.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:53:57 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/29 03:36:11 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <string.h>
#include <signal.h>

void	reception(int sig, siginfo_t *info, void *content)
{
	(void) info;
	(void) content;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		msh_status_set(130);
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_gestionnary(void)
{
	struct sigaction	s_sigaction;

	bzero(&s_sigaction, sizeof(struct sigaction));
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = reception;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
}
