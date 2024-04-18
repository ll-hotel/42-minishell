/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:54:37 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/18 14:22:26 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	parse_quoted(char *cut, int quote);
long		parse_env_var(t_env *env, char *str, char *str_j);
void		*insert_new_args(t_token *arg);

t_llst	*parse_quotes(t_env *env, char **cuts)
{
	t_llst_head	arg_lst;
	t_token		*arg;
	long		i;
	long		j;
	long		tmp;

	arg_lst.first = char_array_to_token(cuts);
	free_array((void **)cuts);
	if (!arg_lst.first)
		return (NULL);
	i = 0;
	arg = (void *)arg_lst.first;
	while (arg)
	{
		j = 0;
		while (arg->str[j])
		{
			while (arg->str[j] && !is_quote(arg->str[j]))
			{
				if (arg->str[j] == '$')
				{
					tmp = parse_env_var(env, arg->str, arg->str + j);
					if (tmp < 0 && insert_new_args(arg) == NULL)
						return (llst_clear(&arg_lst, &token_delete), NULL);
				}
				j++;
			}
			if (is_quote(arg->str[j]))
				j += parse_quoted(&(arg->str[j]), arg->str[j]);
		}
		arg = arg->next;
		i++;
	}
	return (arg_lst.first);
}

static long	parse_quoted(char *cut, int quote)
{
	char	*closing_quote;

	closing_quote = ft_strchr(cut + 1, quote);
	if (!closing_quote)
	{
		ft_dprintf(2, "-- ERROR: \"%s\"\n", cut);
		exit(127);
	}
	ft_memmove(closing_quote, closing_quote + 1, ft_strlen(closing_quote));
	ft_memmove(cut, cut + 1, ft_strlen(cut));
	return (closing_quote - cut - 1);
}

t_env_var	*env_find_var(t_env *env, char *name)
{
	const int	name_length = ft_strlen(name) + 1;
	t_env_var	*var;

	var = (void *)env->vars.first;
	while (var && ft_strncmp(var->name, name, name_length))
		var = var->next;
	return (var);
}

long	parse_env_var(t_env *env, char **str, char *str_j)
{
	t_env_var	*var;
	int			var_value_length;
	long		tmp;
	long		i;

	i = 1;
	while (ft_isalnum(str_j[i]) || str_j[i] == '_')
		i += 1;
	tmp = str_j[i];
	str_j[i] = 0;
	var = env_find_var(env, str_j + 1);
	str_j[i] = tmp;
	ft_memmove(str_j, str_j + i, ft_strlen(str_j + i) + 1);
	if (!var || !var->value)
		return (i);

	// Realloc str to contain env var value

	var_value_length = ft_strlen(var->value);
	i = ft_strlen(*str);
	tmp = (long)ft_realloc(*str, i, i + var_value_length + 1);
	if (!tmp)
		return (-1);
	*str = (void *)tmp;
	
	// Insert env var value
	
	ft_memmove(*str + var_value_length, *str, i);
	ft_memmove(*str, var->value, var_value_length);

	return (i);
}

void	*insert_new_args(t_token *arg, int start, int end)
{
	int		len;
	char	*str;
	void	*token;
	long	i;

	str = arg->str;
	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i += 1;
		ft_memmove(str, str + i, len - i + 1);
		i = 0;
		while (str[i] && !is_space(str[i]))
			i += 1;
		if (is_space(str[i]))
		{
			arg->str = ft_substr(str, 0, i);
			if (!arg->str)
				return (NULL);
			arg->type = arg->str[0];
			ft_memmove(str, str + i, len - i + 1);
			i = 0;
		}
		if (i == 0)
		{
			token = token_new(NULL, 0);
			if (!token)
				return (NULL);
			llst_addfront((t_llst_head *)arg, token);
			arg = arg->next;
		}
	}
	return (arg);
}
