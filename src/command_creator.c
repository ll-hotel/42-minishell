/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/21 15:00:00 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_arg(t_token **token, t_env *env);
static char	*create_arg_tail(t_token **token, t_env *env);
static char	*arg_tail_double_quoted(t_token **token, t_env *env);

t_command	*command_creator(t_token *token, t_env *env)
{
	t_command	*cmd;
	t_vec		argv;
	char		*arg;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	vec_new(&argv, sizeof(arg));
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type != TOKEN_SPACE)
		{
			arg = create_arg(&token, env);
			if (!arg || !vec_addback(&argv, arg))
				return (command_free(cmd), NULL);
		}
		if (token && token->type == TOKEN_SPACE)
			token = token->next;
	}
	if (!vec_addback(&argv, NULL))
		command_free(cmd);
	cmd->argv = argv.array;
	cmd->argc = argv.size - 1;
	return (cmd);
}

static char	*create_arg(t_token **token, t_env *env)
{
	char	*arg;
	char	*tail;
	char	*tmp;

	arg = ft_strdup("");
	while (token[0] && token[0]->type != TOKEN_SPACE)
	{
		tmp = NULL;
		tail = create_arg_tail(token, env);
		if (tail)
			tmp = ft_strjoin(arg, tail);
		tail = ft_free(tail);
		arg = ft_free(arg);
		if (!tmp)
			return (NULL);
		arg = tmp;
		if (token[0] && token[0]->type != TOKEN_SPACE)
			token[0] = token[0]->next;
	}
	return (arg);
}

static char	*create_arg_tail(t_token **token, t_env *env)
{
	char	*tail;

	if (!token[0])
		return (NULL);
	tail = NULL;
	if (token[0]->type == TOKEN_WORD)
		tail = token[0]->str;
	else if (token[0]->type == TOKEN_SIMPLE_QUOTE)
	{
		tail = "";
		token[0] = token[0]->next;
		if (token[0])
		{
			if (token[0]->type == TOKEN_DOLLAR)
				tail = "$";
			else if (token[0]->type == TOKEN_WORD)
				tail = token[0]->str;
		}
	}
	else if (token[0]->type == TOKEN_DOLLAR)
	{
		token[0] = token[0]->next;
		if (token[0] && token[0]->type == TOKEN_WORD)
			tail = token[0]->str;
		else
			tail = "$";
	}
	else if (token[0]->type == TOKEN_DOUBLE_QUOTE)
		return (arg_tail_double_quoted(token, env));
	if (!tail)
		return (ft_dprintf(2, "ERROR: TAIL DOES NOT EXIST\n"), NULL);
	return (ft_strdup(tail));
}

static char	*arg_tail_double_quoted(t_token **token, t_env *env)
{
	t_env_var	*var;
	char		*tmp;
	char		*tail;
	long		tail_len;

	(void)env;
	tail = NULL;
	tail_len = 0;
	token[0] = token[0]->next;
	while (token[0] && token[0]->type != TOKEN_DOUBLE_QUOTE)
	{
		if (token[0]->type == TOKEN_WORD)
		{
			tmp = (char *)tail_len;
			tail_len += ft_strlen(token[0]->str);
			tmp = ft_realloc(tail, (unsigned long)tmp, tail_len);
			if (!tmp)
				return (ft_dprintf(2, "Realloc failed!\n"), NULL);
			tail = tmp;
			ft_strlcat(tail, token[0]->str, tail_len);
		}
		else if (token[0]->type == TOKEN_ENV_VAR)
		{
			var = env_var_get(env, token[0]->str);
			tmp = (char *)tail_len;
			tail_len += ft_strlen(var->value);
			tmp = ft_realloc(tail, (unsigned long)tmp, tail_len);
			if (!tmp)
				return (ft_dprintf(2, "Realloc failed!\n"), NULL);
			tail = tmp;
			ft_strlcat(tail, var->value, tail_len);
		}
	}
	return (tail);
}
