/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:32:14 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/17 03:36:32 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_quote(char *str, size_t *i);

t_token	*lexer_heredoc(char *line, int *p_i)
{
	size_t	i;
	char	*limiter;

	*p_i = 2;
	i = 2;
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (!line[i] || line[i] == '|')
	{
		msh_syntax_err(line[i]);
		return (NULL);
	}
	*p_i = i;
	while (line[i] && !ft_isblank(line[i]))
	{
		if (ft_is_quote(line, &i) == -1)
			return (NULL);
		i += (line[i] != 0);
	}
	limiter = ft_substr(line, *p_i, i - *p_i);
	*p_i = i;
	return (token_new(limiter, TOKEN_HEREDOC));
}

static int	ft_is_quote(char *str, size_t *i)
{
	char	quote;

	if (str[*i] != '\'' && str[*i] != '\"')
		return (0);
	quote = str[*i];
	*i += 1;
	*i += ft_strichr(str + *i, quote);
	if (!str[*i])
	{
		msh_syntax_err(0);
		return (-1);
	}
	return (0);
}
