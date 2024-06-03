/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/31 15:56:51 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_command(t_token *token);
static char	*create_arg(t_command *cmd, t_token *token, int *pnext);
static char	*arg_redirect(t_llst_head *redirects, t_token *token);

t_command	*command_creator(t_llst_head *tokenlst_head)
{
	t_llst_head	cmdlst_head;
	void		*cmd;
	t_token		*token;

	cmdlst_head.first = NULL;
	token = (t_token *)tokenlst_head->first;
	while (token)
	{
		cmd = create_command(token);
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

static t_command	*create_command(t_token *token)
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
		arg = create_arg(cmd, token, &to_next);
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

static char	*create_arg(t_command *cmd, t_token *token, int *pnext)
{
	char	*arg;

	arg = NULL;
	*pnext = 1;
	if (token->type == TOKEN_WORD)
		arg = ft_strdup(token->str);
	else if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || token->type == TOKEN_HEREDOC)
		arg = arg_redirect(&cmd->redirections, token);
	if (!arg)
		*pnext = 0;
	return (arg);
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
