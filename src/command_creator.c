/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/07 10:59:24 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_arg(t_token **token, t_env *env);
static char	*create_arg_tail(t_token **token, t_env *env);
static char	*arg_tail_double_quoted(t_token **token, t_env *env);

t_command	*command_creator(t_token *token, t_env *env)
{
	t_command	*cmd;
	char		*arg;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	vec_new(&cmd->argv, sizeof(arg));
	while (token && token->type != TOKEN_PIPE)
	{
		if (token->type != TOKEN_SPACE)
		{
			arg = create_arg(&token, env);
			if (!arg || !vec_addback(&cmd->argv, arg))
				return (command_free(cmd), NULL);
		}
		if (token && token->type == TOKEN_SPACE)
			token = token->next;
	}
	if (!vec_addback(&cmd->argv, NULL))
		command_free(cmd);
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
	return (ft_strdup(tail));
}

static char	*arg_tail_double_quoted(t_token **token, t_env *env)
{
	char	*tmp;
	char	*tail;

	(void)tmp;
	(void)env;
	tail = NULL;
	token[0] = token[0]->next;
	while (token[0] && token[0]->type != TOKEN_DOUBLE_QUOTE)
	{
	}
	return (tail);
}
