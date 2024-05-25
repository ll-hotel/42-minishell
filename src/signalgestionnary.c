/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalgestionnary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 02:53:57 by lrichaud          #+#    #+#             */
/*   Updated: 2024/05/25 18:41:49 by lrichaud         ###   ########lyon.fr   */
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
		return ;
	else if (sig == SIGQUIT)
		return ;

}

void	signal_gestionnary(void)
{
	struct sigaction	s_sigaction;

	ft_printf("PID : %d\n", getpid());
	bzero(&s_sigaction, sizeof(struct sigaction));
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = reception;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
}
