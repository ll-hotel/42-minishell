/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:38:30 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/30 10:22:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	return (c == '$' \
			|| c == '\'' || c == '\"' \
			|| c == '|' || c == '<' || c == '>');
}

void	*lexer_word(char *str, int *i)
{
	const int	start = *i;
	char		*tmp;

	while (str[*i] && !is_operator(str[*i]))
		*i += 1;
	tmp = ft_substr(str, start, *i - start);
	if (tmp)
		return (token_new(tmp, TOKEN_WORD));
	return (NULL);
}

void	*lexer_operator(char *str, int *i)
{
	char const	op = str[(*i)++];
	char		*tmp;

	if (op == '$')
		return (token_new(NULL, TOKEN_DOLLAR));
	else if (op == '\'')
		return (token_new(NULL, TOKEN_SIMPLE_QUOTE));
	else if (op == '\"')
		return (token_new(NULL, TOKEN_DOUBLE_QUOTE));
	else if (op == '|')
		return (token_new(NULL, TOKEN_PIPE));
	else if (op == '<' || op == '>')
	{
		tmp = ft_substr(&op, 0, 1);
		if (tmp)
			return (token_new(tmp, TOKEN_REDIRECT));
	}
	return (NULL);
}
