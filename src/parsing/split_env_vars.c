/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:55:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/02 23:26:43 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_env_vars(t_token *head)
{
	t_token	*tmp;
	char	**p_word;
	char	**words;

	while (head->next)
	{
		if (head->next->type == TOKEN_ENV_VAR)
		{
			words = ft_splat(head->next->str, " \t");
			if (!words)
				return (0);
			p_word = words;
			if (!*p_word)
			{
				ft_free_parray(words);
				llst_delone((t_llst_head *)head, token_free);
				continue ;
			}
			head->next->type = TOKEN_WORD;
			free(head->next->str);
			head->next->str = *(p_word++);
			while (*p_word)
			{
				head = head->next;
				tmp = token_new(NULL, TOKEN_SPACE);
				if (!tmp)
					return (ft_free_array(p_word), free(words), 0);
				llst_addfront((t_llst_head *)head, (t_llst *)tmp);
				head = head->next;
				tmp = token_new(*p_word, TOKEN_WORD);
				if (!tmp)
					return (ft_free_array(p_word), free(words), 0);
				llst_addfront((t_llst_head *)head, (t_llst *)tmp);
				p_word += 1;
			}
			words = ft_free(words);
		}
		else
			head = head->next;
	}
	return (1);
}
