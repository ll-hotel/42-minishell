/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:09:21 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:09:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_redir(char *line, int *p_i)
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
		return (msh_syntax_err(line[offset]), NULL);
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
