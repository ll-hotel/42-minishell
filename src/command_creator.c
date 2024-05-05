/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/24 18:53:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_arg(t_command *cmd, t_token *token, t_env *env, int *pnext);
static char	*arg_env_var(char *token_str, t_env *env);
static char	*arg_redirect(t_llst_head *redirects, t_token *token);
static t_command	*create_command(t_token *token, t_env *env);

t_command	*command_creator(t_llst_head *tokenlst_head, t_env *env)
{
	t_llst_head	cmdlst_head;
	void		*cmd;
	t_token		*token;

	cmdlst_head.first = NULL;
	token = (t_token *)tokenlst_head->first;
	while (token)
	{
		cmd = create_command(token, env);
		if (!cmd)
		{
			llst_clear(&cmdlst_head, &command_free);
			return (NULL);
		}
		llst_addback(&cmdlst_head, cmd);
		while (token && token->type != TOKEN_PIPE)
			token = token->next;
		if (token)
			token = token->next;
	}
	return ((t_command *)cmdlst_head.first);
}

static t_command	*create_command(t_token *token, t_env *env)
{
	t_command	*cmd;
	t_vec		argv;
	char		*arg;
	int			to_next;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	vec_new(&argv, sizeof(arg));
	while (token && token->type != TOKEN_PIPE)
	{
		arg = create_arg(cmd, token, env, &to_next);
		token = (t_token *)llst_at((t_llst_head *)token, to_next - 1);
		if ((!arg && !to_next) || \
				(arg != (char *)1 && !vec_addback(&argv, arg)))
			return (command_free(cmd), NULL);
	}
	if (!vec_addback(&argv, NULL))
		return (command_free(cmd), NULL);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->argv = argv.array;
	cmd->argc = argv.size - 1;
	return (cmd);
}

static char	*create_arg(t_command *cmd, t_token *token, t_env *env, int *pnext)
{
	char	*arg;

	arg = NULL;
	*pnext = 1;
	if (token->type == TOKEN_WORD || token->type == TOKEN_SIMPLE_QUOTE)
		arg = ft_strdup(token->str);
	else if (token->type == TOKEN_ENV_VAR)
		arg = arg_env_var(token->str, env);
	else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT)
		arg = arg_redirect(&cmd->redirections, token);
	if (!arg)
		*pnext = 0;
	return (arg);
}

static char	*arg_env_var(char *token_str, t_env *env)
{
	t_env_var	*evar;

	if (!token_str[0])
		return (ft_strdup("$"));
	if (!ft_strncmp(token_str, "?", 2))
		return (ft_itoa(env->last_exit_status));
	evar = env_var_get(env, token_str);
	if (evar)
		return (ft_strdup(evar->value));
	return ((char *)1);
}

static char	*arg_redirect(t_llst_head *redirects, t_token *token)
{
	t_token	*token_dup;

	token_dup = ft_memdup(token, sizeof(*token));
	if (token_dup)
	{
		token_dup->next = NULL;
		token_dup->str = ft_strdup(token->str);
		if (!token_dup->str)
			return (ft_free(token_dup));
		llst_addback(redirects, (t_llst *)token_dup);
	}
	return ((char *)(long)(token_dup != NULL));
}
