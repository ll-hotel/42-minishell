/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:46:14 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/27 19:26:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_parser_expand(t_token *head, t_env *env);
static int	msh_parser_evar_split(t_token *head);
static void	msh_parser_remove_spaces(t_token *head);

int	msh_parser(t_llst_head *token_lst, t_env *env)
{
	if (!msh_parser_expand((t_token *)token_lst, env))
		return (0);
	if (!msh_parser_evar_split((t_token *)token_lst))
		return (0);
	msh_parser_remove_spaces((t_token *)token_lst);
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
			return (0);
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

static void	msh_parser_remove_spaces(t_token *head)
{
	t_token	*tmp_head;

	tmp_head = head;
	while (tmp_head->next)
	{
		if (tmp_head->next->type == TOKEN_SPACE)
			llst_delone((t_llst_head *)tmp_head, token_free);
		else
			tmp_head = tmp_head->next;
	}
}
