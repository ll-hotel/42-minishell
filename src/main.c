/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/27 22:14:29 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static const char	*token_type_str(int type);
static t_token		*tokenize(char *line);
static t_command	*get_command(t_llst_head *tokenlst_head, t_msh *msh);

static void	msh_on_line(t_msh *msh, char *line);
void	signal_gestionnary(void);

int	main(int argc, char **argv, char *const *envp)
{
	t_msh	msh;
	char	*line;

	(void)argv;
	signal_gestionnary();
	if (argc != 1)
		return (1);
	ft_bzero(&msh, sizeof(msh));
	if (!env_init(&msh.env, envp))
		return (1);
	//welcome_test_subject();
	while (1)
	{
		line = display_prompt();
		if (!line)
			break ;
		msh_on_line(&msh, line);
	}
	msh_exit(&msh, 0);
}

static void	msh_on_line(t_msh *msh, char *line)
{
	msh->args.first = (t_llst *)tokenize(line);
	msh->cmds.first = (t_llst *)get_command(&msh->args, msh);
	llst_clear(&msh->args, &token_free);
	if (msh->cmds.first)
		msh->env.last_exit_status = msh_exec(msh, (t_command *)msh->cmds.first);
	llst_clear(&msh->cmds, &command_free);
}

/*
   t_token	*token;
   for (token = first_arg; token; token = token->next)
   {
   printf("%s", token_type_str(token->type));
   if (token->str)
   printf(" `%s'", token->str);
   printf("\n");
   }
   */
static t_token	*tokenize(char *line)
{
	t_token	*first_arg;

	first_arg = lexer_line(line);
	return (first_arg);
}

/*
   int	i;
   if (cmd)
	   for (i = 0; i < cmd->argc; i++)
		   printf("`%s' ", cmd->argv[i]);
   printf("\n");
   */
static t_command	*get_command(t_llst_head *tokenlst_head, t_msh *msh)
{
	t_command	*cmd;

	if (!syntax_checker((t_token *)tokenlst_head->first))
		return (NULL);
	cmd = command_creator(tokenlst_head, &msh->env);
#if 0
   int	i;
   for (t_command *_cmd = cmd; _cmd; _cmd = _cmd->next) {
	   for (i = 0; i < _cmd->argc; i++)
		   printf("`%s' ", _cmd->argv[i]);
	   printf("%s", _cmd->next ? "| " : "");
   }
   printf("\n");
#endif
	if (!cmd)
		ft_dprintf(2, "minishell: failed to create command\n");
	return (cmd);
}

/*
 * TOKEN_WORD,
 * TOKEN_SIMPLE_QUOTE,
 * TOKEN_DOUBLE_QUOTE,
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
