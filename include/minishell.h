/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/04/17 23:55:10 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "llst.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*	----	ENVIRONMENT	----	*/

typedef struct s_env_var
{
	void	*next;
	char	*name;
	char	*value;
}	t_env_var;

typedef struct s_env
{
	t_llst_head	vars;
	int			last_return_value;
}	t_env;

int		env_init(t_env *env, char *const *penv);
void	*env_var_new(char *p);
void	env_var_delete(void *var);

/*	----	TOKEN	----	*/

typedef struct s_token
{
	void	*next;
	char	*str;
	int		type;
}	t_token;

void	*token_new(char *str, int type);
void	token_delete(void *token);
t_llst	*char_array_to_token(char **cuts);


/*	----	CUTTER	----	*/

typedef struct s_cutter
{
	size_t	word_len;
	int		start_word;
	int		nb_args;
}	t_cutter;

int		args_counter(char *str);
char	**init_args_array(char *args);
char	**cutter(char *args);
t_llst	*parse_quotes(char **cuts);


/*	----	UTILS	----	*/

void	welcome_test_subject(void);
char	*display_prompt(void);
int		is_space(char c);
int		is_quote(char c);
void	free_array(void **ptr);

#endif
