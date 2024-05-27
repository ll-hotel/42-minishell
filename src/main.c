/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/27 19:42:53 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static const char	*token_type_str(int type);
static t_command	*get_command(t_llst_head *tokenlst_head);

static void	msh_on_line(t_msh *msh, char *line);

int	main(int argc, const char **argv, char *const *envp)
{
	t_msh	msh;
	char	*line;

	if (argc != 1)
		return (1);
	ft_bzero(&msh, sizeof(msh));
	if (!env_init(&msh.env, envp))
		return (1);
	welcome_test_subject();
	line = display_prompt();
	while (line)
	{
		msh_on_line(&msh, line);
		line = display_prompt();
	}
	msh_exit(&msh, 0);
}

static void	msh_on_line(t_msh *msh, char *line)
{
	if (!line)
		return ;
	msh->args.first = (t_llst *)lexer_line(line);
	if (!msh_parser(&msh->args, &msh->env))
	{
		ft_dprintf(2, "minishell: parser failed\n");
		return ;
	}
	msh->cmds.first = (t_llst *)get_command(&msh->args);
	llst_clear(&msh->args, &token_free);
	if (msh->cmds.first)
		msh->env.last_exit_status = msh_exec(msh, (t_command *)msh->cmds.first);
	llst_clear(&msh->cmds, &command_free);
}

static t_command	*get_command(t_llst_head *tokenlst_head)
{
	t_command	*cmd;

	if (!syntax_checker((t_token *)tokenlst_head->first))
		return (NULL);
	cmd = command_creator(tokenlst_head);
	if (!cmd)
		ft_dprintf(2, "minishell: failed to create command\n");
	return (cmd);
}

/*
 * TOKEN_WORD,
 * TOKEN_SIMPLE_QUOTE,
 * TOKEN_DQUOTE,
 * TOKEN_ENV_VAR,
 * TOKEN_REDIR_IN,
 * TOKEN_REDIR_OUT,
 * TOKEN_PIPE
 */
/*
static const char	*token_type_str(int type)
{
	const char	*description[] = {
		"word",
		"  \' ",
		"  \" ",
		"  $ ",
		"  < ",
		"  > ",
		"  | "
	};

	if (type <= TOKEN_PIPE)
		return (description[type]);
	return (" ???");
}
*/
