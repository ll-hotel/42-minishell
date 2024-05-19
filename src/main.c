/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/19 19:27:26 by ll-hotel         ###   ########.fr       */
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

void	ft_free_parray(void *array)
{
	void	**p;

	if (array)
	{
		p = array;
		if (p)
			while (*p)
				free(*(p++));
		free(array);
	}
}

static t_token		*tokenize(char *line);
static t_command	*get_command(t_token *token_lst, t_env *env);

int	main(int argc, const char **argv, char *const *penv)
{
	t_env		env;
	t_llst_head	args;
	t_llst_head	cmds;
	char		*line;

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
		args.first = (t_llst *)tokenize(line);
		cmds.first = (t_llst *)get_command((t_token *)args.first, &env);
		env.last_return_value = pipex((t_command *)cmds.first, &env);
		llst_clear(&cmds, (void *)&command_free);
		llst_clear(&args, &token_delete);
		if (env.last_return_value == I_AM_CHILD)
		{
			llst_clear(&env.vars, &env_var_delete);
			exit(-1);
		}
		printf("%d\n", env.last_return_value);
	}
	llst_clear(&env.vars, &env_var_delete);
	return (0);
}

static t_token	*tokenize(char *line)
{
	char	**cuts;
	t_token	*token_lst;

	cuts = cutter(line);
	if (!cuts)
		return (NULL);
	token_lst = lexer_on_cuts(cuts);
	ft_free_parray(cuts);
	for (t_token *token = token_lst; token; token = token->next)
		printf("%s\t\t`%s'\n", token_type_str(token->type), token->str ? token->str : "");
	printf("\n");
	return (token_lst);
}

static t_command	*get_command(t_token *token_lst, t_env *env)
{
	t_command	*cmd;

	if (!grammary_checker(token_lst))
		return (ft_dprintf(2, "Invalid command\n"), NULL);
	cmd = command_creator(token_lst, env);
	if (cmd)
	{
		for (int i = 0; i < cmd->argc; i++)
		{
			printf("`%s'", cmd->argv[i]);
			printf("%c", i + 1 < cmd->argc ? ' ' : '\n');
		}
	}
	else
		ft_dprintf(2, "Failed to create command\n");
	return (cmd);
}
