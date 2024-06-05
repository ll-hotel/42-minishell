/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:19:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/06/05 18:25:34 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

int	parser_heredoc(t_token *head, t_msh *msh)
{
	(void) msh;
	//char	*bagarre;
	char	*str;
	int		fd_pipe[2];

	while (head->next && head->next->type != TOKEN_HEREDOC)
		head = head->next;
	if (!head->next)
		return (1);
	if (pipe(fd_pipe) == -1)
	{
		perror("heredoc");
		return (0);
	}
	str = readline("");
	while (!ft_strnstr(str, head->next->str, ft_strlen(str)))
	{
		// bagarre = ft_strchr(str, '$');
		// while (bagarre)
		// {
		// 	str = heredoc_expand(msh, str, bagarre);
		// 	bagarre = ft_strchr(str, '$');
		// }

		write(fd_pipe[1], str, ft_strlen(str));
		free(str);
		str = readline("");
	}
	free(head->next->str);
	free(str);
	head->next->fd = fd_pipe[0];
	close(fd_pipe[1]);
	return (1);
}