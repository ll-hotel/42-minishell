/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/23 12:24:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LLST_H
# define LLST_H

typedef struct s_llst_head	t_llst_head;
typedef struct s_llst		t_llst;

struct	s_llst_head
{
	t_llst	*first;
};

struct	s_llst
{
	t_llst	*next;
};

void	llst_addback(t_llst_head *lst, t_llst *element);
void	llst_addfront(t_llst_head *lst, t_llst *element);
t_llst	*llst_at(t_llst_head *lst_head, int i);
void	llst_clear(t_llst_head *lst, void (*f)(void *));
void	llst_delone(t_llst_head *lst, void (*f)(void *));
t_llst	*llst_get_last(t_llst_head *lst);
long	llst_len(t_llst_head *lst);
t_llst	*llst_next(t_llst_head *lst);

#endif
