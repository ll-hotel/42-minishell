/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 19:44:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	ch_on_line(t_ch *ch, char *line);

int	main(int argc, char **argv, char *const *envp)
{
	t_ch	ch;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (1);
	ft_bzero(&ch, sizeof(ch));
	if (!ch_env_init(&ch, envp))
		return (1);
	while (1)
	{
		signal_gestionnary();
		line = display_prompt(&ch);
		if (!line)
			break ;
		ch_on_line(&ch, line);
		free(line);
	}
	ft_putstr_fd("exit\n", 1);
	ch_exit(&ch, ch_status_get());
}

static void	ch_on_line(t_ch *ch, char *line)
{
	if (!line)
		return ;
	ch->args.first = (t_llst *)lexer_line(line);
	if (ch_parser(&ch->args, ch))
	{
		ch->cmds.first = (t_llst *)cmd_creator(&ch->args);
		llst_clear(&ch->args, &token_free);
		if (ch->cmds.first)
			ch_exec(ch);
		llst_clear(&ch->cmds, &cmd_free);
	}
	else
		llst_clear(&ch->args, &token_free);
}
