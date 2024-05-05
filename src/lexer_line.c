/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:04:25 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 14:19:35 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lexer_token(char *line, int *new_i);

t_token	*lexer_line(char *line)
{
	t_llst_head	token_lst;
	t_token		*token;
	int			i;
	int			new_i;

	if (!line)
		return (NULL);
	token_lst.first = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isblank(line[i]))
			i += 1;
		if (!line[i])
			continue ;
		token = lexer_token(line + i, &new_i);
		if (!token)
		{
			llst_clear(&token_lst, &token_free);
			return (NULL);
		}
		llst_addback(&token_lst, (t_llst *)token);
		i += new_i;
	}
	return ((t_token *)token_lst.first);
}

static t_token	*lexer_token(char *line, int *new_i)
{
	const char	c = *line;
	int			word_len;
	t_token		*token;

	token = NULL;
	word_len = 0;
	if (c == '\'')
		token = lexer_simple_quote(line + 1, &word_len);
	else if (c == '$')
		token = lexer_dollar(line + 1, &word_len);
	else if (c == '<' || c == '>')
		token = lexer_redirection(line, &word_len);
	else if (c == '|')
	{
		word_len = 1;
		token = token_new(NULL, TOKEN_PIPE);
	}
	else
		token = lexer_word(line, &word_len);
	*new_i = word_len + (c == '\'' || c == '\"');
	return (token);
}
