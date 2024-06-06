/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/06 13:38:45 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_command(t_llst_head *tokenlst_head);
static void			msh_on_line(t_msh *msh, char *line);
void				signal_gestionnary(void);

int	main(int argc, char **argv, char *const *envp)
{
	t_msh	msh;
	char	*line;

	(void)argv;
	signal_gestionnary();
	if (argc != 1)
		return (1);
	ft_bzero(&msh, sizeof(msh));
	if (!env_init(&msh, envp))
		return (1);
	while (1)
	{
		line = display_prompt();
		if (!line)
			break ;
		msh_on_line(&msh, line);
	}
	msh_exit(&msh, msh_status_get_error());
}

static void	msh_on_line(t_msh *msh, char *line)
{
	if (!line)
		return ;
	msh->args.first = (t_llst *)lexer_line(line);
	if (msh_parser(&msh->args, msh))
	{
		msh->cmds.first = (t_llst *)get_command(&msh->args);
		llst_clear(&msh->args, &token_free);
		if (msh->cmds.first)
			msh_exec(msh);
		llst_clear(&msh->cmds, &command_free);
	}
	else
		llst_clear(&msh->args, &token_free);
}

static t_command	*get_command(t_llst_head *tokenlst_head)
{
	t_command	*cmd;

	cmd = command_creator(tokenlst_head);
	if (!cmd)
		msh_status_set(2);
	return (cmd);
}
