/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 18:55:07 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*parse_double_quotes(t_llst_head *tokens_head);
static void	*parse_env_vars(t_llst_head *tokens_head, t_env *env);

void	*parser(t_llst_head *tokens_head, t_env *env)
{
	if (!parse_double_quotes(tokens_head))
		return (NULL);
	if (!parse_env_vars(tokens_head, env))
		return (NULL);
	return (tokens_head->first);
}

static void	*parse_double_quotes(t_llst_head *tokens_head)
{
	t_llst_head	*tmp_head;
	t_token		*tok;
	char		in_double_quotes;
	char		in_simple_quotes;

	tmp_head = tokens_head;
	in_double_quotes = 0;
	in_simple_quotes = 0;
	while (tmp_head->first)
	{
		tok = (t_token *)tmp_head->first;
		if (tok->type == TOKEN_SIMPLE_QUOTE)
			in_simple_quotes = !in_double_quotes * !in_simple_quotes;
		else if (tok->type == TOKEN_DOUBLE_QUOTE)
			in_double_quotes = !in_simple_quotes * !in_double_quotes;
		else if (tok->type == TOKEN_DOLLAR && !in_simple_quotes)
		{
			llst_delone(tmp_head, &token_delete);
			tok = (t_token *)tmp_head->first;
			if (tok && tok->type == TOKEN_WORD)
				tok->type = TOKEN_ENV_VAR;
		}
		tmp_head = (t_llst_head *)tmp_head->first;
	}
	return (tokens_head->first);
}

//			ENVIRONMENT VARIABLES HANDLING

/*
static void	*expand_env_var(t_llst_head *env_var_head)
{
	t_token	*tok;

	tok = (t_token *)env_var_head->first;

	

	return (env_var_head->first);
}
*/

static void	*insert_env_var(t_llst_head *env_var_head, t_env *env, int quoted)
{
	t_env_var	*var;
	t_token		*tok;

	(void)quoted;
	tok = (t_token *)env_var_head->first;
	var = env_var_get(env, tok->str);
	if (tok->str)
		tok->str = (free(tok->str), NULL);
	if (var)
	{
		tok->str = ft_strdup(var->value);
		if (!tok->str)
			return (NULL);
	}
	//if (quoted)
		tok->type = TOKEN_WORD;
	/*
	else
	{
		tok = expand_env_var(env_var_head);
		if (!tok)
			return (NULL);
	}
	*/
	return (env_var_head->first);
}

static void	*parse_env_vars(t_llst_head *tokens_head, t_env *env)
{
	t_llst_head	*tmp_head;
	t_token		*tok;
	char		in_double_quotes;
	char		in_simple_quotes;

	tmp_head = tokens_head;
	in_double_quotes = 0;
	in_simple_quotes = 0;
	while (tmp_head->first)
	{
		tok = (t_token *)tmp_head->first;
		if (tok->type == TOKEN_SIMPLE_QUOTE)
			in_simple_quotes = !in_double_quotes * !in_simple_quotes;
		else if (tok->type == TOKEN_DOUBLE_QUOTE)
			in_double_quotes = !in_simple_quotes * !in_double_quotes;
		else if (tok->type == TOKEN_ENV_VAR)
		{
			tok = insert_env_var(tmp_head, env, in_simple_quotes || in_double_quotes);
			if (!tok)
				return (NULL);
		}
		tmp_head = (t_llst_head *)tmp_head->first;
	}
	return (tokens_head->first);
}
