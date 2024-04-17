/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/18 00:10:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#if 0
static void	display_tokens(void *p)
{
	t_token	*token;
	int			i;

	i = 0;
	token = p;
	while (token)
	{
		ft_dprintf(2, "token [%d] %s\n", token->type, token->str);
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
		args.first = parse_quotes(cuts);
		llst_clear(&args, &token_delete);
		line = display_prompt();
	}
	llst_clear(&env.vars, &env_var_delete);
	return (0);
}
