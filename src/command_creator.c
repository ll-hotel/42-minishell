/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/04 16:51:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*loop(t_token **token, t_env *env);

t_command	*command_creator(t_token *token, t_env *env)
{
	t_command	*cmd;
	t_vec		vec_argv;
	char		*arg;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	vec_new(&vec_argv, sizeof(char *));
	while (token)
	{
		if (token->type != TOKEN_SPACE)
		{
			arg = loop(&token, env);
			if (!arg || !vec_addback(&vec_argv, arg))
				return (vec_clear(&vec_argv, NULL), ft_free(cmd));
		}
		token = token->next;
	}
	cmd->argc = vec_argv.size;
	cmd->argv = ft_calloc(cmd->argc + 1, sizeof(*cmd->argv));
	if (!cmd->argv)
		return (ft_free(cmd));
	ft_memmove(cmd->argv, vec_argv.array, cmd->argc * sizeof(*cmd->argv));
	vec_clear(&vec_argv, NULL);
	return (cmd);
}

static char	*loop_double_quotes(t_token **token, t_env *env);

static char	*loop(t_token **token, t_env *env)
{
	void	*tmp;

	tmp = "";
	if (token[0]->type == TOKEN_DOLLAR && token[0]->next)
	{
		*token = token[0]->next;
		if (token[0]->type != TOKEN_WORD)
			return (ft_strdup("$"));
		return (ft_strdup("ENV_VAR"));
	}
	if (token[0]->type == TOKEN_WORD)
		return (ft_strdup(token[0]->str));
	else if (token[0]->type == TOKEN_SIMPLE_QUOTE && token[0]->next)
	{
		*token = token[0]->next;
		if (token[0]->type == TOKEN_WORD)
			tmp = token[0]->str;
		if (token[0]->next && token[0]->next->type == TOKEN_SIMPLE_QUOTE)
			*token = token[0]->next;
		return (ft_strdup(tmp));
	}
	else if (token[0]->type == TOKEN_DOUBLE_QUOTE)
		return (loop_double_quotes(token, env));
	return (NULL);
}

static char	*loop_double_quotes(t_token **token, t_env *env)
{
	char	*tmp;
	char	*arg;

	(void)(env);
	arg = NULL;
	*token = token[0]->next;
	while (*token && token[0]->type != TOKEN_DOUBLE_QUOTE)
	{
		if (token[0]->type == TOKEN_WORD)
		{
			tmp = ft_strjoin(arg, token[0]->str);
			arg = ft_free(arg);
			if (!tmp)
				return (NULL);
			arg = tmp;
		}
		else if (token[0]->type == TOKEN_DOLLAR)
		{
			*token = token[0]->next;
			if (token[0]->type != TOKEN_WORD)
				tmp = ft_strjoin(arg, "$");
			else
				tmp = ft_strjoin(arg, token[0]->str);
			arg = ft_free(arg);
			if (!tmp)
				return (NULL);
			arg = tmp;
		}
		if (token[0]->type == TOKEN_WORD)
			*token = token[0]->next;
	}
	return (arg);
}
