/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_evars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 02:55:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/05 17:17:57 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minichell.h"

static int	for_each_word(char **words, t_token **head);

int	split_evars(t_token *head)
{
	char	**words;

	while (head->next)
	{
		if (head->next->type == TOKEN_ENV_VAR)
		{
			words = ft_splat(head->next->str, " \t");
			if (!words)
				return (0);
			if (!words[0])
			{
				ft_free_parray(words);
				llst_delone((t_llst_head *)head, token_free);
				continue ;
			}
			if (!for_each_word(words, &head))
				return (0);
		}
		else
			head = head->next;
	}
	return (1);
}

static int	for_each_word(char **words, t_token **head)
{
	t_token	*tmp;
	char	**p_word;

	p_word = words;
	head[0]->next->type = TOKEN_WORD;
	free(head[0]->next->str);
	head[0]->next->str = *(p_word++);
	while (*p_word)
	{
		*head = head[0]->next;
		tmp = token_new(NULL, TOKEN_SPACE);
		if (!tmp)
			return (ft_free_array(p_word), free(words), 0);
		llst_addfront((t_llst_head *)*head, (t_llst *)tmp);
		*head = head[0]->next;
		tmp = token_new(*p_word, TOKEN_WORD);
		if (!tmp)
			return (ft_free_array(p_word), free(words), 0);
		llst_addfront((t_llst_head *)*head, (t_llst *)tmp);
		p_word += 1;
	}
	words = ft_free(words);
	return (1);
}
