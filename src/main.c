/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/02 15:51:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define CUTS 0
#define TOKENIZER 0
#define ASSEMBLE 0

#if TOKENIZER
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

static void	display_tokens(void *p)
{
	t_token	*token;
	int		i;

	if (!p)
		return ;
	i = 0;
	token = p;
	while (token)
	{
		ft_dprintf(2, "[%d] (%s)", i++, token_type_str(token->type));
		if (token->str)
			ft_dprintf(2, "\t    %s", token->str);
		ft_dprintf(2, "\n");
		token = token->next;
	}
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
#if TOKENIZER | ASSEMBLE
	void		*tmp;
#endif
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
			args.first = lexer_on_cuts(cuts);
			ft_free_parray((void **)cuts);
			cuts = NULL;
		}
		if (grammary_checker((t_token *)args.first))
		{
#if 1
			cmd = command_creator((t_token *)args.first);
			if (cmd)
			{
				for (int i = 0; i < cmd->argc; i++)
					printf("%s%c", cmd->argv[i], \
							' ' * (i + 1 < cmd->argc) + '\n' * (i + 1 == cmd->argc));
				command_free(cmd);
				cmd = NULL;
			}
			else
				ft_dprintf(2, "Failed to create command\n");
#endif
		}
		else
			ft_dprintf(2, "Invalid command\n");
		llst_clear(&args, &token_delete);
	}
	llst_clear(&env.vars, &env_var_delete);
	return (0);
}
