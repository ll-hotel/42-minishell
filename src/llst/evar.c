/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evar.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:19:08 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/17 22:18:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static char	*evar_join(t_evar *var);

char	**ch_to_array(t_evar *evar_head)
{
	const long	evar_nb = llst_len((t_llst_head *)evar_head);
	char		**envp;
	long		i;

	envp = ft_calloc(evar_nb + 1, sizeof(*envp));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < evar_nb)
	{
		envp[i++] = evar_join(evar_head->next);
		evar_head = evar_head->next;
	}
	return (envp);
}

t_evar	*evar_new(char *envp_var)
{
	t_evar		*var;
	uint32_t	i;

	var = ft_calloc(1, sizeof(*var));
	if (!var)
		return (NULL);
	i = 0;
	while (envp_var[i] && envp_var[i] != '=')
		i += 1;
	var->name = ft_substr(envp_var, 0, i);
	if (!var->name)
		return (ft_free(var));
	if (envp_var[i] == '=')
	{
		var->value = ft_substr(envp_var, i + 1, ft_strlen(envp_var) - i - 1);
		if (!var->value)
		{
			evar_free(var);
			return (NULL);
		}
	}
	return (var);
}

t_evar	*find_evar(t_ch *ch, char *name)
{
	int const	name_len = ft_strlen(name);
	t_evar		*var;

	var = (t_evar *)ch->evars.first;
	while (var && ft_strncmp(var->name, name, name_len + 1))
		var = var->next;
	return (var);
}

void	evar_free(void *var)
{
	ft_free(((t_evar *)var)->name);
	ft_free(((t_evar *)var)->value);
	ft_free(var);
}

static char	*evar_join(t_evar *var)
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
