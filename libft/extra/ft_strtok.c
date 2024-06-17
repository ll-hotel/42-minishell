/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:13:56 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 00:47:33 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isdelim(char c, const char *delim);
static void	null_terminate_tok(char **tok, const char *delim, char **next);

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next = 0;
	char		*tok;

	if (str)
		tok = str;
	else
		tok = next;
	next = 0;
	null_terminate_tok(&tok, delim, &next);
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

static void	null_terminate_tok(char **tok, const char *delim, char **next)
{
	char	*tmp;

	tmp = *tok;
	*tok = 0;
	if (!tmp || !tmp[0])
		return ;
	if (isdelim(tmp[0], delim))
		*(tmp++) = 0;
	while (isdelim(tmp[0], delim))
		tmp += 1;
	if (!tmp[0])
		return ;
	*tok = tmp;
	while (tmp[0] && !isdelim(tmp[0], delim))
		tmp += 1;
	if (tmp[0])
	{
		tmp[0] = 0;
		*next = tmp + 1;
	}
}
