/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammary_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:09:06 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/30 12:14:17 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(t_token	*token)
{
	t_command	tmp_command;
	t_command	*ret_command;
	int			in_out;

	ft_bzero(&tmp_command, sizeof(tmp_command));
	vec_new(&tmp_command.arguments, sizeof(char *));

	while (token)
	{
		if (token->type == TOKEN_WORD && tmp_command.executable == NULL)
		{
			tmp_command.executable = token->str;
			if (!vec_addback(&tmp_command.arguments, tmp_command.executable))
				return (NULL);
		}
		else if (token->type == TOKEN_WORD)
		{
			if (!vec_addback(&tmp_command.arguments, token->str))
				return (NULL);
		}
		else if (token->type == TOKEN_SIMPLE_QUOTE || token->type == TOKEN_DOUBLE_QUOTE)
		{
			char	t[2] = {0};
			void	*tmp;
			void	*str;

			t[0] = '\'' * (token->type == TOKEN_SIMPLE_QUOTE) + \
					'\"' * (token->type == TOKEN_DOUBLE_QUOTE);

			token = token->next;
			if (!token || token->type != TOKEN_WORD)
				return (ft_dprintf(2, "Syntax error near token `%c`\n", t[0]), NULL);
			tmp = ft_strjoin(t, token->str);
			token = token->next;
			str = ft_strjoin(tmp, t);
			if (tmp)
				free(tmp);
			if (!str || !vec_addback(&tmp_command.arguments, str))
				return (NULL);
		}
		else if (token->type == TOKEN_REDIRECT)
		{
			in_out = token->str[0];
			token = token->next;
			if (in_out == '<' && token->type == TOKEN_WORD)
				tmp_command.file_in = token->str;
			else if (in_out == '>' && token->type == TOKEN_WORD)
				tmp_command.file_out = token->str;
			else
				return (ft_dprintf(2, "Syntax error near token `%c`\n", in_out), NULL);
		}
		if (token)
			token = token->next;
	}

	ret_command = ft_calloc(1, sizeof(*ret_command));
	if (ret_command)
		ft_memmove(ret_command, &tmp_command, sizeof(tmp_command));
	return (ret_command);
}
