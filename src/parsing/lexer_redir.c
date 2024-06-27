/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:09:21 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/27 15:47:09 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

t_token	*lexer_redir(char *line, int *p_i)
{
	const int	type = *line;
	int			i;

	i = 1;
	while (ft_isblank(line[i]))
		i += 1;
	if (!line[i] || line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		ch_syntax_err(line[i]);
		return (NULL);
	}
	*p_i = i;
	if (type == '<')
		return (token_new(NULL, TOKEN_REDIR_IN));
	return (token_new(NULL, TOKEN_REDIR_OUT));
}
