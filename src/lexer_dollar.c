/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:09:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/26 05:09:46 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
