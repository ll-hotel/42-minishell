/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/23 23:10:38 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*parser_insert_env_var(t_token *name, t_env *env);

static void	move_head_forward(t_llst_head *head, t_token **token)
{
	void	*tmp;

	tmp = token[0]->next;
	free(*token);
	head->first = tmp;
	*token = tmp;
}

void	*parser(t_llst_head *token_lst, t_env *env)
{
	t_llst_head	head;
	t_token		*token;

	head.first = token_lst->first;
	token = (t_token *)head.first;
	while (token)
	{
		if (token->type == TOKEN_SIMPLE_QUOTE)
		{
			move_head_forward(&head, &token);
			while (token && token->type != TOKEN_SIMPLE_QUOTE)
				token = token->next;
		}
		else if (token->type == TOKEN_DOUBLE_QUOTE)
		{
			token = token->next;
			while (token && token->type != TOKEN_DOUBLE_QUOTE)
			{
				if (token->type == TOKEN_DOLLAR)
					token = parser_insert_env_var(token, env);
				if (token)
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
	return (token_lst);
}

static void	*parser_insert_env_var(t_token *dollar, t_env *env)
{
	t_token		*token_var;

	(void)env;
	token_var = dollar->next;
	if (token_var->type != TOKEN_WORD || token_var->str == NULL)
	{
		;
	}
	return (NULL);
}
