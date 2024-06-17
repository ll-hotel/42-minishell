/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:43:27 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/04 21:57:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

t_token	*lexer_append(char *line, int *p_i)
{
	int	i;

	i = 2;
	while (ft_isblank(line[i]))
		i += 1;
	if (!line[i] || line[i] == '|' || line[i] == '<' || line[i] == '>')
		return (ch_syntax_err(line[i]), NULL);
	*p_i = i;
	return (token_new(NULL, TOKEN_APPEND));
}
