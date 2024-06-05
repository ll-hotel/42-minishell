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

int	ft_is_quote(char c, char *str, size_t *i);

t_token	*lexer_heredoc(char *line, int *p_i)
{
	size_t	i;

	i = 2;
	*p_i = 2;
	while (ft_isblank(line[i]))
		i++;
	while (!ft_isblank(line[i]))
	{
		if(ft_is_quote(line[i], line, &i) == -1)
			return (NULL);
		i++;
	}
	*p_i = i;
	return (token_new(line, TOKEN_HEREDOC));
}

int	ft_is_quote(char c, char *str, size_t *i)
{
	char	temp;

	if (c == '\'' || c == '\"')
	{
		temp = c;
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

	// i = 0;
	// while (!ft_isblank(end_sequence[i]) && end_sequence[i])
	// 	i++;
	// end_sequence = ft_substr(end_sequence, 0, i);
	// *p_i += i;
	// str = readline("");
	// while (!ft_strnstr(str, end_sequence, ft_strlen(str)))
	// {
	// 	bagarre = ft_strchr(str, '$');
	// 	while (bagarre)
	// 	{
	// 		str = heredoc_expand(msh, str, bagarre);
	// 		bagarre = ft_strchr(str, '$');
	// 	}

	// 	write(fd_pipe[1], str, ft_strlen(str));
	// 	str = readline("");
	// }
	// close(fd_pipe[1]);


