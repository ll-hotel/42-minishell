/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llst.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:45 by ll-hotel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/27 15:31:06 by ll-hotel         ###   ########.fr       */
=======
/*   Updated: 2024/04/17 22:54:23 by ll-hotel         ###   ########.fr       */
>>>>>>> main
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
void	llst_delone(t_llst_head *lst, void (*f)(void *));
void	llst_clear(t_llst_head *lst, void (*f)(void *));
long	llst_len(t_llst_head *lst);

#endif
