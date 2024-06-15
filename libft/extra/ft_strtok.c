/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:13:56 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/16 01:46:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isdelim(char c, const char *delim);
static void	null_terminate_tok(char *tok, const char *delim, char **next);

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next = 0;
	char		*tok;

	if (!str)
	{
		tok = next;
		null_terminate_tok(tok, delim, &next);
	}
	else
	{
		if (!*str)
			return (0);
		while (*str && isdelim(*str, delim))
			str += 1;
		tok = str;
		null_terminate_tok(tok, delim, &next);
	}
	return (tok);
}

static int	isdelim(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i] && c != delim[i])
		i += 1;
	return (delim[i] != 0);
}

static void	null_terminate_tok(char *tok, const char *delim, char **next)
{
	if (!tok)
		return ;
	while (*tok && !isdelim(*tok, delim))
		tok += 1;
	if (!*tok)
	{
		*next = 0;
		return ;
	}
	*tok = 0;
	tok += 1;
	while (*tok && isdelim(*tok, delim))
		tok += 1;
	if (!*tok)
		*next = 0;
	else
		*next = tok;
}
