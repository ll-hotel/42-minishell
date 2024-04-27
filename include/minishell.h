/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/27 18:30:26 by ll-hotel         ###   ########.fr       */
=======
/*   Updated: 2024/04/19 00:00:52 by ll-hotel         ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
void	*env_var_get(t_env *env, char *name);
=======
>>>>>>> main
void	env_var_delete(void *var);

/*	----	TOKEN	----	*/

enum	e_token_type
{
<<<<<<< HEAD
	TOKEN_SPACE,
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_SIMPLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_DOLLAR,
	TOKEN_ENV_VAR,
	TOKEN_REDIRECT,
	TOKEN_PIPE
=======
	TOKEN_WORD,
	TOKEN_SPACE,
	TOKEN_SIMPLE_QUOTE = '\'',
	TOKEN_DOUBLE_QUOTE = '\"',
	TOKEN_DOLLAR,
	TOKEN_OPERATOR
>>>>>>> main
};

typedef struct s_token
{
	void	*next;
	char	*str;
	int		type;
}	t_token;

void	*token_new(char *str, int type);
void	token_delete(void *token);
t_llst	*char_array_to_token(char **cuts);

<<<<<<< HEAD
=======

>>>>>>> main
/*	----	CUTTER	----	*/

typedef struct s_cutter
{
	size_t	word_len;
	int		start_word;
	int		nb_words;
}	t_cutter;

char	**cutter(char *line);
char	**cutter_init_words(char *line);
t_llst	*init_args(char *line);
size_t	quote_reader(char *str, ssize_t i, char quote_type);

<<<<<<< HEAD
/*	----	LEXER	----	*/

void	*lexer_on_cuts(char **cuts);
void	*lexer_operator(char *str, int *i);
void	*lexer_word(char *str, int *i);
int		is_operator(int c);

/*	----	PARSER	----	*/

void	*parser(t_llst_head *tokens_head, t_env *env);
char	*parser_assemble(t_token *token);
=======
void	*lexer_on_cuts(char **cuts);
>>>>>>> main

/*	----	UTILS	----	*/

void	welcome_test_subject(void);
char	*display_prompt(void);
int		is_space(char c);
int		is_quote(char c);
void	free_array(void **ptr);

#endif
