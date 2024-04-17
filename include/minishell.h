/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 21:43:44 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "llst.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum	e_ret_status
{
	RET_OK,
	RET_ERROR = -1
};

typedef struct s_cutter
{
	size_t	word_len;
	int		start_word;
	int		nb_args;
}	t_cutter;

typedef struct s_token
{
	void	*next;
	char	*str;
	int		type;
}	t_token;

void	*token_new(char *str, int type);
void	token_delete(void *token);
t_llst	*char_array_to_token(char **cuts);

void	welcome_test_subject(void);
char	*display_prompt(void);
char	**cutter(char *args);
t_llst	*parse_quotes(char **cuts);

/*	UTILS	*/

/*	is space (32) or tabulation	*/
int		is_space(char c);
int		is_quote(char c);

int		args_counter(char *str);
char	**init_args_array(char *args);

#endif
