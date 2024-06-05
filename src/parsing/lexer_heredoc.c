/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:32:14 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/04 19:06:54 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_quote(char *str, size_t *i);

t_token	*lexer_heredoc(char *line, int *p_i)
{
	size_t	i;
	char	*limiter;

	*p_i = 2;
	i = 2;
	while (line[i] && ft_isblank(line[i]))
		i++;
	*p_i = i;
	while (line[i] && !ft_isblank(line[i]))
	{
		if(ft_is_quote(line, &i) == -1)
			return (NULL);
		i++;
	}
	limiter = ft_substr(line, *p_i, i - *p_i);
	*p_i = i;
	return (token_new(limiter, TOKEN_HEREDOC));
}

int	ft_is_quote(char *str, size_t *i)
{
	char	temp;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		temp = str[*i];
		while (str[*i] && str[*i] != temp)
			(*i)++;
		if (!str[*i])
		{
			write(1, "Quote Error\n", 12);
			return (-1);
		}
	}
	return (0);
}



