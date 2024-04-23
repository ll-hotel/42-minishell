/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/20 17:15:36 by ll-hotel         ###   ########.fr       */
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

void	llst_addfront(t_llst_head *lst, t_llst *element);
void	llst_addback(t_llst_head *lst, t_llst *element);
void	*llst_get_last(t_llst_head *lst);
void	llst_clear(t_llst_head *lst, void (*f)(void *));
long	llst_len(t_llst_head *lst);

#endif
