/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/19 16:26:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DISPLAY_TOKENS
#ifdef DISPLAY_TOKENS
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
		ft_dprintf(2, "token[%d] (%s)", i++, token_type_str(token->type));
		if (token->str)
			ft_dprintf(2, "\t    %s", token->str);
		ft_dprintf(2, "\n");
		token = token->next;
	}
}
#endif

int	main(int argc, const char **argv, char *const *penv)
{
	t_env		env;
	t_llst_head	args;
	char		*line;
	char		**cuts;

	if (argc != 1)
	{
		if (ft_strncmp(argv[1], "-c", 3))
			return (1);
		return (0);
	}
	if (!env_init(&env, penv))
		return (1);
	welcome_test_subject();
	line = display_prompt();
	while (line)
	{
		cuts = cutter(line);
		args.first = lexer_on_cuts(cuts);
		for (int i = 0; cuts && cuts[i]; i++)
			ft_dprintf(2, "CUT %d // %s\n", i, cuts[i]);
#ifdef DISPLAY_TOKENS
		display_tokens(args.first);
		char	*command = parser_assemble((t_token *)args.first);
		ft_dprintf(2, "COMMAND -> `%s`\n", command);
		if (command)
			free(command);
#endif
		llst_clear(&args, &token_delete);
		line = display_prompt();
	}
	llst_clear(&env.vars, &env_var_delete);
	return (0);
}
