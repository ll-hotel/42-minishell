/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_on_cuts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:04:25 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/19 00:05:04 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*lexer_on_cut(t_llst_head *token_lst, char *cut);
static void	*lexer_operator(char *str, int *i);
static void	*lexer_word(char *str, int *i);
static int	is_token(int c);

void	*lexer_on_cuts(char **cuts)
{
	t_llst_head	token_lst;
	void		*space;

	if (!cuts)
		return (NULL);
	token_lst.first = NULL;
	while (*cuts)
	{
		if (!lexer_on_cut(&token_lst, *(cuts++)))
		{
			llst_clear(&token_lst, &token_delete);
			return (NULL);
		}
		if (!*cuts)
			break ;
		space = token_new(NULL, TOKEN_SPACE);
		if (!space)
		{
			llst_clear(&token_lst, &token_delete);
			return (NULL);
		}
		llst_addback(&token_lst, space);
	}
	return (token_lst.first);
}

static void	*lexer_on_cut(t_llst_head *token_lst, char *cut)
{
	void	*token;
	int		i;

	i = 0;
	while (cut[i])
	{
		token = NULL;
		if (is_quote(cut[i]))
			token = token_new(NULL, cut[i++]);
		else if (cut[i] == '$')
		{
			token = token_new(NULL, TOKEN_DOLLAR);
			i += 1;
		}
		else if (cut[i] == '|')
			token = lexer_operator(cut, &i);
		else
			token = lexer_word(cut, &i);
		if (!token)
			return (NULL);
		llst_addback(token_lst, token);
	}
	return (token);
}

static void	*lexer_operator(char *str, int *i)
{
	char	*tmp;

	tmp = ft_substr(str, *i, 1);
	*i += 1;
	if (tmp)
		return (token_new(tmp, TOKEN_OPERATOR));
	return (NULL);
}

static void	*lexer_word(char *str, int *i)
{
	const int	start = *i;
	char		*tmp;

	while (str[*i] && !is_token(str[*i]))
		*i += 1;
	tmp = ft_substr(str, start, *i - start);
	if (tmp)
		return (token_new(tmp, TOKEN_WORD));
	return (NULL);
}

static int	is_token(int c)
{
	return (c == '$' \
			|| c == '\'' || c == '\"' \
			|| c == '|');
}
