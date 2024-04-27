/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:17:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/27 15:38:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_delete(void *token)
{
	if (!token)
		return ;
	if (((t_token *)token)->str)
	{
		free(((t_token *)token)->str);
		((t_token *)token)->str = NULL;
	}
	free(token);
}

void	*token_new(char *str, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	return (token);
}

t_llst	*char_array_to_token(char **cuts)
{
	t_llst_head	lst;
	void		*token;

	if (!cuts)
		return (NULL);
	lst.first = NULL;
	while (*cuts)
	{
		token = token_new(ft_strdup(*cuts), **cuts);
		token = token_new(ft_strdup(*cuts), **cuts);
		if (!token)
		{
			llst_clear(&lst, &token_delete);
			return (NULL);
		}
		llst_addback(&lst, token);
		cuts += 1;
	}
	return (lst.first);
}
