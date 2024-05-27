/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:27:49 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/27 19:08:09 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_empty(char **p_str);
static void	expand_status(t_env *env, char **p_str);
static void	expand_pid(char **p_str);
static void	expand_var(t_env *env, char **p_str);

int	env_var_expand(t_llst_head *env_var, t_env *env)
{
	t_token		*token;

	token = (t_token *)env_var->first;
	if (token->str[0] == 0)
		expand_empty(&token->str);
	else if (ft_strncmp(token->str, "?", 2) == 0)
		expand_status(env, &token->str);
	else if (ft_strncmp(token->str, "$", 2) == 0)
		expand_pid(&token->str);
	else
		expand_var(env, &token->str);
	return (token->str != NULL);
}

static void	expand_empty(char **p_str)
{
	free(*p_str);
	*p_str = ft_strdup("$");
}

static void	expand_status(t_env *env, char **p_str)
{
	free(*p_str);
	*p_str = ft_itoa(env->last_exit_status);
}

static void	expand_pid(char **p_str)
{
	free(*p_str);
	*p_str = ft_itoa(getpid());
}

static void	expand_var(t_env *env, char **p_str)
{
	t_env_var	*evar;

	evar = env_var_get(env, *p_str);
	free(*p_str);
	if (!evar)
		*p_str = ft_calloc(1, 1);
	else
		*p_str = ft_strdup(evar->value);
}
