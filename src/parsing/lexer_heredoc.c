/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:32:14 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/17 13:05:00 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"
#include <unistd.h>

static int	ft_is_quote(char *str, size_t *i);
static char	*cut_delimiter(char *line, int *p_i);
static void	remove_quotes(char *delimiter);

t_token	*lexer_heredoc(char *line, int *p_i)
{
	uint64_t	i;
	char		*delimiter;
	t_token		*heredoc_token;

	delimiter = cut_delimiter(line, p_i);
	if (!delimiter)
	{
		perror("miniChell");
		return (NULL);
	}
	i = 0;
	while (delimiter[i] && delimiter[i] != '\'' && delimiter[i] != '\"')
		i += 1;
	remove_quotes(delimiter);
	heredoc_token = token_new(delimiter, TOKEN_HEREDOC);
	if (heredoc_token)
		heredoc_token->fd = (delimiter[i] != 0);
	return (heredoc_token);
}

static char	*cut_delimiter(char *line, int *p_i)
{
	size_t	i;
	char	*limiter;

	*p_i = 2;
	i = 2;
	while (line[i] && ft_isblank(line[i]))
		i++;
	if (!line[i] || line[i] == '|')
	{
		ch_syntax_err(line[i]);
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
	return (limiter);
}

static void	remove_quotes(char *delimiter)
{
	uint64_t	closing_quote;

	while (*delimiter)
	{
		if (*delimiter == '\'' || *delimiter == '\"')
		{
			closing_quote = ft_strichr(delimiter + 1, '\'');
			ft_memmove(delimiter + 1 + closing_quote, \
					delimiter + 2 + closing_quote, \
					ft_strlen(delimiter + 1 + closing_quote));
			ft_memmove(delimiter, delimiter + 1, closing_quote + 1);
			delimiter += closing_quote;
		}
		else
			delimiter += 1;
	}
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
		ch_syntax_err(0);
		return (-1);
	}
	return (0);
}
