/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:09:59 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:47:13 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_word(char *line, int *p_i)
{
	const int	squoted = *line == '\'';
	char		*word;
	int			word_len;

	word_len = 0;
	if (squoted)
		word_len = ft_strichr(line + 1, '\'');
	else
		while (line[word_len] \
				&& !ft_isblank(line[word_len]) \
				&& !is_operator(line[word_len]))
			word_len += 1;
	if (squoted && !line[word_len + 1])
		return (msh_syntax_err(-'\''), NULL);
	word = ft_substr(line, squoted, word_len);
	*p_i = word_len + squoted * 2;
	if (word)
		return (token_new(word, TOKEN_WORD));
	return (NULL);
}
