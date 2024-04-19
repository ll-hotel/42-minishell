/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/19 20:41:27 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*parser_insert_env_var(t_token *token_dollar, t_env *env);

void	*parser(t_llst *token_lst, t_env *env)
{
	t_token	*token;

	token = (t_token *)token_lst;
	while (token)
	{
		if (token->type == TOKEN_SIMPLE_QUOTE)
		{
			token = token->next;
			while (token && token->type != TOKEN_SIMPLE_QUOTE)
				token = token->next;
		}
		else if (token->type == TOKEN_DOUBLE_QUOTE)
		{
			token = token->next;
			while (token && token->type != TOKEN_SIMPLE_QUOTE)
			{
				if (token->type == TOKEN_DOLLAR)
					token = parser_insert_env_var(token->next, env);
				if (token)
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
	return (token_lst);
}

char	*parser_assemble(t_token *token)
{
	char	*str;
	void	*joined;

	str = ft_calloc(1, sizeof(*str));
	if (!str)
		return (NULL);
	while (token)
	{
		joined = NULL;
		if (token->type == TOKEN_WORD)
			joined = ft_strjoin(str, token->str);
		else if (token->type == TOKEN_REDIRECT)
			joined = ft_strjoin(str, token->str);
		else if (token->type == TOKEN_SPACE)
			joined = ft_strjoin(str, " ");
		else if (token->type == TOKEN_DOLLAR)
			joined = ft_strjoin(str, "$");
		else if (token->type == TOKEN_SIMPLE_QUOTE)
			joined = ft_strjoin(str, "\'");
		else if (token->type == TOKEN_DOUBLE_QUOTE)
			joined = ft_strjoin(str, "\"");
		else if (token->type == TOKEN_PIPE)
			joined = ft_strjoin(str, "|");
		free(str);
		if (!joined)
			return (NULL);
		str = joined;
		token = token->next;
	}
	return (str);
}

static void	*parser_insert_env_var(t_token *token_dollar, t_env *env)
{
	t_token		*token;
	t_env_var	*var;

	token = token_dollar->next;
	if (token->type != TOKEN_WORD || token->str == NULL)
		return (token);
	var = env_var_get(env, token->str);
	if (!var)
		return (token);
	return (token);
}
