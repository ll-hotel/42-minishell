/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:45 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 20:23:35 by ll-hotel         ###   ########.fr       */
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
void	llst_clear(t_llst_head *lst, void (*f)(void *));

#endif
