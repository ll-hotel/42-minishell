/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:27 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/04 17:49:53 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_append(char *line, int *p_i)
{
	char	*filename;
	int		length;
	int		spaces;

	spaces = 2;
	while (ft_isblank(line[spaces]))
		spaces += 1;
	length = 0;
	line += spaces;
	while (line[length] && !ft_isblank(line[length]) && \
			!is_operator(line[length]))
		length += 1;
	filename = ft_substr(line, 0, length);
	if (!filename)
		return (NULL);
	*p_i = spaces + length;
	return (token_new(filename, TOKEN_APPEND));
}
