/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evar_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:27:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/03 07:03:24 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniChell.h"

static void	expand_empty(char **p_str);
static void	expand_status(char **p_str);
static void	expand_pid(char **p_str);
static void	expand_var(t_ch *ch, char **p_str);

int	evar_expand(t_llst_head *evars, t_ch *ch)
{
	t_token		*token;

	token = (t_token *)evars->first;
	if (token->str[0] == 0)
		expand_empty(&token->str);
	else if (ft_strncmp(token->str, "?", 2) == 0)
		expand_status(&token->str);
	else if (ft_strncmp(token->str, "$", 2) == 0)
		expand_pid(&token->str);
	else
		expand_var(ch, &token->str);
	return (token->str != NULL);
}

static void	expand_empty(char **p_str)
{
	free(*p_str);
	*p_str = ft_strdup("$");
}

static void	expand_status(char **p_str)
{
	free(*p_str);
	*p_str = ft_itoa(ch_status_get());
}

static void	expand_pid(char **p_str)
{
	free(*p_str);
	*p_str = ft_itoa(getpid());
}

static void	expand_var(t_ch *ch, char **p_str)
{
	t_evar	*evar;

	evar = find_evar(ch, *p_str);
	free(*p_str);
	if (!evar)
		*p_str = ft_calloc(1, 1);
	else
		*p_str = ft_strdup(evar->value);
}
