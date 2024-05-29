/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:27:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 03:03:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_empty(char **p_str);
static void	expand_status(char **p_str);
static void	expand_pid(char **p_str);
static void	expand_var(t_msh *msh, char **p_str);

int	env_var_expand(t_llst_head *env_vars, t_msh *msh)
{
	t_token		*token;

	token = (t_token *)env_vars->first;
	if (token->str[0] == 0)
		expand_empty(&token->str);
	else if (ft_strncmp(token->str, "?", 2) == 0)
		expand_status(&token->str);
	else if (ft_strncmp(token->str, "$", 2) == 0)
		expand_pid(&token->str);
	else
		expand_var(msh, &token->str);
	return (token->str != NULL);
}

static void	expand_empty(char **p_str)
{
	free(*p_str);
	*p_str = ft_strdup("$");
}

static void	expand_status(char **p_str)
{
	*p_str = ft_itoa(msh_status_get());
}

static void	expand_pid(char **p_str)
{
	free(*p_str);
	*p_str = ft_itoa(getpid());
}

static void	expand_var(t_msh *msh, char **p_str)
{
	t_env_var	*evar;

	evar = env_var_get(msh, *p_str);
	free(*p_str);
	if (!evar)
		*p_str = ft_calloc(1, 1);
	else
		*p_str = ft_strdup(evar->value);
}
