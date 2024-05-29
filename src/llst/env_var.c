/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:19:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/29 02:59:58 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*env_var_join(t_env_var *var);

char	**env_to_array(t_env_var *evar_head)
{
	const long	env_var_nb = llst_len((t_llst_head *)evar_head);
	char		**envp;
	long		i;

	envp = ft_calloc(env_var_nb + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < env_var_nb)
	{
		envp[i++] = env_var_join(evar_head->next);
		evar_head = evar_head->next;
	}
	return (envp);
}

t_env_var	*env_var_new(char *envp_var)
{
	t_env_var		*var;
	unsigned int	i;

	var = ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	i = 0;
	while (envp_var[i] && envp_var[i] != '=')
		i += 1;
	var->name = ft_substr(envp_var, 0, i);
	if (!var->name)
		return (NULL);
	if (envp_var[i] == '=')
	{
		var->value = ft_substr(envp_var, i + 1, ft_strlen(envp_var) - i - 1);
		if (!var->value)
			return (env_var_free(var), NULL);
	}
	return (var);
}

t_env_var	*env_var_get(t_msh *msh, char *name)
{
	int const	name_len = ft_strlen(name);
	t_env_var	*var;

	var = (t_env_var *)msh->env_vars.first;
	while (var && ft_strncmp(var->name, name, name_len + 1))
		var = var->next;
	return (var);
}

void	env_var_free(void *var)
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
		str_len += ft_strlen(var->value) + 2;
	str = ft_calloc(str_len, sizeof(*str));
	if (!str)
		return (NULL);
	ft_strlcat(str, var->name, str_len);
	if (var->value)
		str[name_len] = '=';
	ft_strlcat(str, var->value, str_len);
	return (str);
}
