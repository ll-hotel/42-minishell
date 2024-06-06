/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:17:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/06 15:32:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(void *token)
{
	t_token *const	tok = token;

	if (!tok)
		return ;
	llst_clear(&tok->inner_tokens, token_free);
	tok->fd = ft_close(tok->fd);
	tok->str = ft_free(tok->str);
	free(token);
}

t_token	*token_new(void *str, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->fd = -1;
	return (token);
}
