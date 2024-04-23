/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_assemble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:34:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/20 15:34:30 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser_assemble(t_token *token)
{
	char	*str;
	void	*joined;

	str = ft_calloc(1, sizeof(*str));
	if (!str)
		return (NULL);
	while (token)
	{
		joined = NULL;
		if (token->type == TOKEN_WORD)
			joined = ft_strjoin(str, token->str);
		else if (token->type == TOKEN_REDIRECT)
			joined = ft_strjoin(str, token->str);
		else if (token->type == TOKEN_SPACE)
			joined = ft_strjoin(str, " ");
		else if (token->type == TOKEN_DOLLAR)
			joined = ft_strjoin(str, "$");
		else if (token->type == TOKEN_SIMPLE_QUOTE)
			joined = ft_strjoin(str, "\'");
		else if (token->type == TOKEN_DOUBLE_QUOTE)
			joined = ft_strjoin(str, "\"");
		else if (token->type == TOKEN_PIPE)
			joined = ft_strjoin(str, "|");
		free(str);
		if (!joined)
			return (NULL);
		str = joined;
		token = token->next;
	}
	return (str);
}
