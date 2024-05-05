/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 16:46:34 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	return (c == '$' \
			|| c == '\'' || c == '\"' \
			|| c == '|' || c == '<' || c == '>');
}

t_token	*lexer_word(char *line, int *p_i)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (line[word_len] \
			&& !ft_isblank(line[word_len]) \
			&& !is_operator(line[word_len]))
		word_len += 1;
	word = ft_substr(line, 0, word_len);
	*p_i = word_len;
	if (word)
		return (token_new(word, TOKEN_WORD));
	return (NULL);
}

t_token	*lexer_dollar(char *line, int *p_i)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (line[word_len] \
			&& !ft_isblank(line[word_len]) \
			&& !is_operator(line[word_len]))
		word_len += 1;
	word = ft_substr(line, 0, word_len);
	*p_i = word_len + 1;
	if (word)
		return (token_new(word, TOKEN_ENV_VAR));
	return (NULL);
}

t_token	*lexer_simple_quote(char *line, int *p_i)
{
	char	*word;
	int		word_len;

	word_len = ft_strichr(line, '\'');
	word = ft_substr(line, 0, word_len);
	*p_i = word_len + 1;
	if (word)
		return (token_new(word, TOKEN_SIMPLE_QUOTE));
	return (NULL);
}

t_token	*lexer_redirection(char *line, int *p_i)
{
	const int	type = *line;
	int			offset;
	char		*word;
	int			word_len;

	offset = 1;
	while (ft_isblank(line[offset]))
		offset += 1;
	word_len = offset;
	while (line[word_len] \
			&& !ft_isblank(line[word_len]) \
			&& !is_operator(line[word_len]))
		word_len += 1;
	word_len -= offset;
	if (word_len == 0)
		return (ft_dprintf(2, "minishell: syntax error near token `<'\n"), NULL);
	word = ft_substr(line, offset, word_len);
	*p_i = offset + word_len;
	if (word)
	{
		if (type == '<')
			return (token_new(word, TOKEN_REDIR_IN));
		return (token_new(word, TOKEN_REDIR_OUT));
	}
	return (NULL);
}
