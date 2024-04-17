/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:19 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 21:58:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_llst_head	args;
	t_token		*token;
	char		*temp;
	char		**cuts;
	int			i;

	i = 0;
	welcome_test_subject();
	while (1)
	{
		i = 0;
		temp = display_prompt();
		if (temp)
		{
			cuts = cutter(temp);
			free(temp);
#if 0
			while(cuts && cuts[i])
			{
				printf("cut n%d: %s\n", i, cuts[i]);
				i++;
			}
#endif
			args.first = parse_quotes(cuts);
			free(cuts);
			token = (void *)args.first;
			while(token)
			{
				printf("arg %d: `%s`\n", i, token->str);
				token = token->next;
			}
			llst_clear(&args, &token_delete);
		}
	}
	return (0);
}
