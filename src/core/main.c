/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 14:50:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	msh_on_line(t_msh *msh, char *line);

int	main(int argc, char **argv, char *const *envp)
{
	t_msh	msh;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (1);
	ft_bzero(&msh, sizeof(msh));
	if (!env_init(&msh, envp))
		return (1);
	while (1)
	{
		signal_gestionnary();
		line = display_prompt();
		if (!line)
			break ;
		msh_on_line(&msh, line);
		free(line);
	}
	ft_putstr_fd("exit\n", 1);
	msh_exit(&msh, msh_status_get());
}

static void	msh_on_line(t_msh *msh, char *line)
{
	if (!line)
		return ;
	msh->args.first = (t_llst *)lexer_line(line);
	if (msh_parser(&msh->args, msh))
	{
		msh->cmds.first = (t_llst *)command_creator(&msh->args);
		llst_clear(&msh->args, &token_free);
		if (msh->cmds.first)
			msh_exec(msh);
		llst_clear(&msh->cmds, &command_free);
	}
	else
		llst_clear(&msh->args, &token_free);
}
