/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assemble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:34:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 18:21:14 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_joiner(char *str_left, char *str_right, int type);

char	*parser_assemble(t_token *token)
{
	char	*str;
	char	*joined;

	str = ft_calloc(1, sizeof(*str));
	if (!str)
		return (NULL);
	while (token)
	{
		joined = _joiner(str, token->str, token->type);
		if (!joined)
			return (NULL);
		if (joined != str)
			str = (free(str), joined);
		token = token->next;
	}
	return (str);
}

static char	*_joiner(char *str_left, char *str_right, int type)
{
	if (type == TOKEN_WORD)
		return (ft_strjoin(str_left, str_right));
	else if (type == TOKEN_REDIRECT)
		return (ft_strjoin(str_left, str_right));
	else if (type == TOKEN_SPACE)
		return (ft_strjoin(str_left, " "));
	else if (type == TOKEN_DOLLAR)
		return (ft_strjoin(str_left, "$"));
	else if (type == TOKEN_SIMPLE_QUOTE)
		return (ft_strjoin(str_left, "\'"));
	else if (type == TOKEN_DOUBLE_QUOTE)
		return (ft_strjoin(str_left, "\""));
	else if (type == TOKEN_PIPE)
		return (ft_strjoin(str_left, "|"));
	return (str_left);
}
