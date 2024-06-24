/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 11:59:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int		loop_body(t_llst_head *cmd_head, t_token **p_token);
static t_cmd	*create_cmd(t_token *token);
static char		*create_arg(t_cmd *cmd, t_token *token, int *pnext);
static char		*arg_redir(t_llst_head *redirs, t_token *token);

t_cmd	*cmd_creator(t_llst_head *tokenlst_head)
{
	t_llst_head	cmd_head;
	t_token		*token;

	cmd_head.first = NULL;
	token = (t_token *)tokenlst_head->first;
	while (token)
	{
		if (loop_body(&cmd_head, &token) != 1)
			return (NULL);
	}
	return ((t_cmd *)cmd_head.first);
}

static int	loop_body(t_llst_head *cmd_head, t_token **p_token)
{
	t_cmd	*cmd;

	cmd = create_cmd(p_token[0]);
	if (!cmd)
		return (0);
	if (cmd->argc == 0)
		ch_syntax_err('|');
	if (cmd->argc == 0)
		return (0);
	llst_addback(cmd_head, (t_llst *)cmd);
	while (p_token[0] && p_token[0]->type != TOKEN_PIPE)
		p_token[0] = p_token[0]->next;
	if (p_token[0])
	{
		*p_token = p_token[0]->next;
		if (p_token[0] == NULL || (p_token[0] && p_token[0]->type == TOKEN_PIPE))
		{
			if (!*p_token)
				ch_syntax_err(0);
			else
				ch_syntax_err('|');
			return (0);
		}
	}
	return (1);
}

static t_cmd	*create_cmd(t_token *token)
{
	t_cmd	*cmd;
	t_vec	argv;
	char	*arg;
	int		to_next;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (perror("miniChell"), NULL);
	vec_new(&argv, sizeof(arg));
	while (token && token->type != TOKEN_PIPE)
	{
		arg = create_arg(cmd, token, &to_next);
		token = (t_token *)llst_at((t_llst_head *)token, to_next - 1);
		if ((!arg && !to_next) || \
				(arg != (char *)1 && !vec_addback(&argv, arg)))
			return (cmd_free(cmd), NULL);
	}
	if (!vec_addback(&argv, NULL))
		return (perror("miniChell"), cmd_free(cmd), NULL);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->argv = argv.array;
	cmd->argc = argv.size - 1;
	return (cmd);
}

static char	*create_arg(t_cmd *cmd, t_token *token, int *pnext)
{
	char	*arg;

	arg = NULL;
	*pnext = 1;
	if (token->type == TOKEN_WORD)
		arg = ft_strdup(token->str);
	else if (token->type == TOKEN_REDIR_IN || \
			token->type == TOKEN_REDIR_OUT || \
			token->type == TOKEN_HEREDOC || \
			token->type == TOKEN_APPEND)
		arg = arg_redir(&cmd->redirs, token);
	if (!arg)
		*pnext = 0;
	return (arg);
}

static char	*arg_redir(t_llst_head *redirs, t_token *token)
{
	t_token	*dup;

	dup = token_new(NULL, token->type);
	if (!dup)
	{
		perror("miniChell");
		ch_status_set(1);
		return (NULL);
	}
	if (dup->type == TOKEN_REDIR_IN || dup->type == TOKEN_REDIR_OUT || \
			dup->type == TOKEN_APPEND)
		dup->str = token->str;
	else if (dup->type == TOKEN_HEREDOC)
		dup->fd = token->fd;
	token->str = NULL;
	token->fd = -1;
	llst_addback(redirs, (t_llst *)dup);
	return ((char *)1);
}
