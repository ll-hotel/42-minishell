/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:46:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 15:45:36 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_parser_expand(t_token *head, t_env *env);
static int	msh_parser_dquote(t_token *head, t_env *env);
static int	msh_parser_evar_split(t_token *head);
static int	msh_parser_remove_spaces(t_token *head);

int	msh_parser(t_llst_head *token_lst, t_env *env)
{
	if (!msh_parser_expand((t_token *)token_lst, env))
		return (0);
	if (!msh_parser_evar_split((t_token *)token_lst))
		return (0);
	if (!msh_parser_remove_spaces((t_token *)token_lst))
		return (0);
	return (1);
}

static int	msh_parser_expand(t_token *head, t_env *env)
{
	while (head->next)
	{
		if (head->next->type == TOKEN_ENV_VAR)
		{
			if (!env_var_expand((t_llst_head*)head, env))
				return (0);
		}
		if (head->next->type == TOKEN_DQUOTE)
		{
			if (!msh_parser_dquote(head, env))
				return (0);
		}
		head = head->next;
	}
	return (1);
}

static int	msh_parser_evar_split(t_token *head)
{
	t_token	*tmp;
	char	**p_word;
	char	**words;

	while (head->next)
	{
		if (head->next->type == TOKEN_ENV_VAR)
		{
			words = ft_splat(head->next->str, " \t");
			if (!words)
				return (0);
			p_word = words;
			if (!*p_word)
			{
				ft_free_parray(words);
				llst_delone((t_llst_head *)head, token_free);
				continue ;
			}
			// This is now a word
			head->next->type = TOKEN_WORD;
			free(head->next->str);
			head->next->str = *(p_word++);
			// Start of split arguments
			while (*p_word)
			{
				// Spacing
				head = head->next;
				tmp = token_new(NULL, TOKEN_SPACE);
				if (!tmp)
					return (ft_free_array(p_word), free(words), 0);
				llst_addfront((t_llst_head *)head, (t_llst *)tmp);
				// New word/arg
				head = head->next;
				tmp = token_new(*p_word, TOKEN_WORD);
				if (!tmp)
					return (ft_free_array(p_word), free(words), 0);
				llst_addfront((t_llst_head *)head, (t_llst *)tmp);
				p_word += 1;
			}
			words = ft_free(words);
		}
		else
			head = head->next;
	}
	return (1);
}

static int	msh_parser_dquote(t_token *head, t_env *env)
{
	t_token	*subtoken;
	char	*joined;

	subtoken = (t_token *)head->next->inner_tokens.first;
	if (!subtoken)
		return (0);
	while (subtoken->next)
	{
		if (subtoken->next->type == TOKEN_ENV_VAR && \
				!env_var_expand((t_llst_head *)subtoken, env))
			return (0);
		joined = ft_strjoin(subtoken->str, subtoken->next->str);
		subtoken->str = ft_free(subtoken->str);
		if (!joined)
			return (0);
		subtoken->str = joined;
		llst_delone((t_llst_head *)subtoken, token_free);
	}
	joined = subtoken->str;
	subtoken->str = NULL;
	token_free(subtoken);
	head->next->str = joined;
	head->next->type = TOKEN_WORD;
	return (1);
}

static int	msh_parser_remove_spaces(t_token *head)
{
	char	*joined;

	while (head->next)
	{
		if (head->next->type == TOKEN_SPACE)
			llst_delone((t_llst_head *)head, token_free);
		else if (head->next->type == TOKEN_WORD)
		{
			while (head->next->next && head->next->next->type == TOKEN_WORD)
			{
				joined = ft_strjoin(head->next->str, head->next->next->str);
				if (!joined)
					return (0);
				free(head->next->str);
				head->next->str = joined;
				llst_delone((t_llst_head *)head->next, token_free);
			}
			head = head->next;
		}
		else
			head = head->next;
	}
	return (1);
}
