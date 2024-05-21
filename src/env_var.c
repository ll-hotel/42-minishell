/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:19:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 14:30:51 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_var_join(t_env_var *var);

char	**env_to_array(t_env *env)
{
	const long	env_var_nb = llst_len(&env->vars);
	t_llst_head	var_lst;
	char		**penv;
	long		i;

	penv = ft_calloc(env_var_nb + 2, sizeof(*penv));
	if (!penv)
		return (NULL);
	i = 0;
	var_lst = env->vars;
	while (i < env_var_nb)
	{
		penv[i++] = env_var_join((t_env_var *)var_lst.first);
		var_lst.first = var_lst.first->next;
	}
	return (penv);
}

t_env_var	*env_var_new(char *penv_var)
{
	t_env_var		*var;
	unsigned int	i;

	var = ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	i = 0;
	while (penv_var[i] && penv_var[i] != '=')
		i += 1;
	var->name = ft_substr(penv_var, 0, i);
	if (!var->name)
		return (NULL);
	if (penv_var[i] == '=')
	{
		var->value = ft_substr(penv_var, i + 1, ft_strlen(penv_var) - i - 1);
		if (!var->value)
			return (env_var_delete(var), NULL);
	}
	return (var);
}

t_env_var	*env_var_get(t_env *env, char *name)
{
	int const	name_len = ft_strlen(name);
	t_env_var	*var;

	var = (t_env_var *)env->vars.first;
	while (var && ft_strncmp(var->name, name, name_len + 1))
		var = var->next;
	return (var);
}

void	env_var_delete(void *var)
{
	ft_free(((t_env_var *)var)->name);
	ft_free(((t_env_var *)var)->value);
	ft_free(var);
}

static char	*env_var_join(t_env_var *var)
{
	char	*str;
	int		name_len;
	int		str_len;

	name_len = ft_strlen(var->name);
	str_len = name_len;
	if (var->value)
		str_len += ft_strlen(var->value) + 1;
	str = ft_calloc(str_len, sizeof(*str));
	if (!str)
		return (NULL);
	ft_memmove(str, var->name, name_len);
	if (var->value)
		str[name_len++] = '=';
	ft_memmove(str + name_len, var->value, str_len - name_len);
	return (str);
}
