/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:04:25 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/04 13:53:08 by lrichaud         ###   ########lyon.fr   */
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
		if (token_lst.first && ft_isblank(line[i - 1]) && \
				((t_token *)llst_get_last(&token_lst))->type != TOKEN_SPACE)
			token = token_new(NULL, TOKEN_SPACE);
		else
			token = lexer_token(line + i, &new_i);
		if (!token)
		{
			llst_clear(&token_lst, &token_free);
			return (NULL);
		}
		llst_addback(&token_lst, (t_llst *)token);
		if (token->type != TOKEN_SPACE)
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
		token = lexer_word(line, &word_len);
	else if (c == '~' || (c == '$' && line[1] != '\'' && line[1] != '\"'))
		token = lexer_dollar(line, &word_len);
	else if (ft_strncmp(line, "<<", 2) == 0)
		token = lexer_heredoc(line, &word_len);
	else if (c == '<' || c == '>')
		token = lexer_redir(line, &word_len);
	else if (c == '|')
	{
		word_len = 1;
		token = token_new(NULL, TOKEN_PIPE);
	}
	else if (c == '\"' || (c == '$' && line[1] == '\"'))
		token = lexer_dquote(line + (c == '$'), &word_len);
	else
		token = lexer_word(line + (c == '$'), &word_len);
	word_len += (c == '$') && (line[1] == '\'' || line[1] == '\"');
	*new_i = word_len;
	return (token);
}
