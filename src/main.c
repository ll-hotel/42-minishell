/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 15:50:19 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_command(t_llst_head *tokenlst_head);
static void	msh_on_line(t_msh *msh, char *line);

int	main(int argc, const char **argv, char *const *envp)
{
	t_msh	msh;
	char	*line;

	(void)argv;
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
#ifdef DEBUG
	printf("------------ Lexer did the following:\n");
	for (t_token *tok = (void *)msh->args.first; tok != NULL; tok = tok->next)
	{
		printf("%d   %p -> ", tok->type, tok->str);
		if (tok->type == TOKEN_DQUOTE)
		{
			printf("{\n");
			for (t_token *subtok = (t_token *)tok->inner_tokens.first; subtok != NULL; subtok=subtok->next)
				printf("    %d   `%s'\n", subtok->type, subtok->str);
			printf("}\n");
		}
		else
			printf("`%s'\n", tok->str);
	}
#endif
	if (!msh_parser(&msh->args, &msh->env))
	{
		ft_dprintf(2, "minishell: parser failed\n");
		return ;
	}
#ifdef DEBUG
	printf("------------ Parser did the following:\n");
	for (t_token *tok = (void *)msh->args.first; tok != NULL; tok = tok->next)
	{
		printf("%d   %p -> ", tok->type, tok->str);
		printf("`%s'\n", tok->str);
	}
#endif
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
		return (printf("Euh nop\n"),NULL);
	cmd = command_creator(tokenlst_head);
	if (!cmd)
		ft_dprintf(2, "minishell: failed to create command\n");
	return (cmd);
}
