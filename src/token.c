/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:17:10 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/22 19:21:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(void *token)
{
	t_token *const	tok = token;

	if (!tok)
		return ;
	tok->str = ft_free(tok->str);
	free(token);
}

t_token	*token_new(char *str, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	return (token);
}
