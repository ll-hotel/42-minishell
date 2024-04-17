/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tok.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 22:57:58 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/12 04:21:22 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKLST_H
# define T_TOKLST_H

typedef struct s_toklst_head	t_toklst_head;
typedef struct s_toklst_node	t_toklst_node;
typedef struct s_tok			t_tok;

struct	s_toklst_head
{
	t_toklst_node	*first;
};

struct	s_toklst_node
{
	t_toklst_node	*next;
};

struct	s_tok
{
	void	*next_node;
	int		type;
	char	*word;
};

enum	e_tok_type
{
	STRING,
	QUOTE,
	DOUBLE_QUOTE,
	ENV_VAR
};

void	*toklst_new(int type, char *word);
void	toklst_addfront(t_toklst_head *lst, t_toklst_node *node);
void	toklst_addback(t_toklst_head *lst, t_toklst_node *node);
void	toklst_clear(t_toklst_head *lst);

#endif
