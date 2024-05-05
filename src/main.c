/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/05 18:12:33 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define TOKENS 1

#if TOKENS
static char	*token_type_str(int type)
{
	if (type == TOKEN_WORD)
		return ("word");
	if (type == TOKEN_SIMPLE_QUOTE)
		return ("simple quote");
	if (type == TOKEN_DOUBLE_QUOTE)
		return ("double quote");
	if (type == TOKEN_PIPE)
		return ("pipe");
	if (type == TOKEN_REDIRECT)
		return ("redirect");
	if (type == TOKEN_SPACE)
		return ("space");
	if (type == TOKEN_DOLLAR)
		return ("dollar");
	return ("???");
}
#endif

void	ft_free_parray(void **array)
{
	unsigned long	i;

	i = 0;
	if (array)
		while (array[i])
			free(array[i++]);
	free(array);
}

int	main(int argc, const char **argv, char *const *penv)
{
	char		**cuts;
	t_env		env;
	t_llst_head	args;
	char		*line;
	t_command	*cmd;

	if (argc != 1)
	{
		// future, for -c integration (string evaluation & run) (see bash -c)
		if (ft_strncmp(argv[1], "-c", 3))
			return (1);
		return (0);
	}
	if (!env_init(&env, penv))
		return (1);
	welcome_test_subject();
	while ((line = display_prompt()))
	{
		cuts = cutter(line);
		if (cuts)
		{
			args.first = (t_llst *)lexer_on_cuts(cuts);
			ft_free_parray((void **)cuts);
			cuts = NULL;
		}
		for (t_token *token = (t_token *)args.first; token; token = token->next)
			printf("%s\t\t`%s'\n", token_type_str(token->type), token->str ? token->str : "");
		printf("\n");
		if (grammary_checker((t_token *)args.first))
		{
			cmd = command_creator((t_token *)args.first, &env);
			if (cmd)
			{
				free(line);
				line = ft_strdup("");
				for (int i = 0; i < cmd->argc; i++)
				{
					printf("`%s'%c", cmd->argv[i], \
							' ' * (i + 1 < cmd->argc) + '\n' * (i + 1 == cmd->argc));
					line = ft_strjoin(line, cmd->argv[i]);
					if (i + 1 < cmd->argc)
						line = ft_strjoin(line, " ");
				}
				chooser(line, &env);
				command_free(cmd);
				cmd = NULL;
			}
			else
				ft_dprintf(2, "Failed to create command\n");
		}
		else
			ft_dprintf(2, "Invalid command\n");
		llst_clear(&args, &token_delete);
	}
	llst_clear(&env.vars, &env_var_delete);
	return (0);
}
