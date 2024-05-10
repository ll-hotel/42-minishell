/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/08 17:59:09 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "llst.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>


/*	----	ENVIRONMENT	----	*/

typedef struct s_env_var	t_env_var;
struct	s_env_var
{
	t_env_var	*next;
	char		*name;
	char		*value;
};

typedef struct s_env	t_env;
struct	s_env
{
	t_llst_head	vars;
	int			last_return_value;
};

int			env_init(t_env *env, char *const *penv);
t_env_var	*env_var_new(char *p);
t_env_var	*env_var_get(t_env *env, char *name);
void		env_var_delete(void *var);
char		**env_to_array(t_env *env);

/*	----	TOKEN	----	*/

enum	e_token_type
{
	TOKEN_SPACE,
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_SIMPLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_DOLLAR,
	TOKEN_ENV_VAR,
	TOKEN_REDIRECT,
	TOKEN_PIPE
};

typedef struct s_token	t_token;
struct	s_token
{
	t_token	*next;
	char	*str;
	int		type;
};

t_token		*token_new(char *str, int type);
void		token_delete(void *token);
t_llst		*char_array_to_token(char **cuts);

/*	----	CUTTER	----	*/

typedef struct s_cutter
{
	size_t	word_len;
	int		start_word;
	int		nb_words;
}			t_cutter;

char		**cutter(char *line);
char		**cutter_init_words(char *line);
t_llst		*init_args(char *line);
size_t		quote_reader(char *str, ssize_t i, char quote_type);

/*	----	LEXER	----	*/

t_token		*lexer_on_cuts(char **cuts);
t_token		*lexer_operator(char *str, int *i);
t_token		*lexer_word(char *str, int *i, char single_quoted);
int			is_operator(int c);

/*	----	PARSER	----	*/

void		*parser(t_llst_head *tokens_head, t_env *env);
char		*parser_assemble(t_token *token);

/*	----	GRAMMARY_CHECKER	----	*/

int			grammary_checker(t_token *token);

/*	----	COMMAND		----	*/

enum	e_redirect
{
	REDIRECT_IN,
	REDIRECT_OUT
};

typedef struct
{
	void	*next;
	char	*name;
	int		fd;
	int		way;
}	t_file;

typedef struct s_command	t_command;
struct	s_command
{
	t_command	*next;
	t_llst_head	redirections;
	int			fd_in;
	int			fd_out;
	char		**path;
	char		*executable;
	int			argc;
	char		**argv;
	char		**penv;
};

t_command	*command_creator(t_token *token, t_env *env);
void		command_free(t_command *command);

/*	----	UTILS	----	*/

void		welcome_test_subject(void);
char		*display_prompt(void);
int			is_space(char c);
int			is_quote(char c);
void		*ft_free(void *p);
int			ft_close(int fd);
void		ft_free_parray(void *array);
short		is_void_command(char *full_command, char *command_word);

/*	----	Buildtsdsfins	----	*/

void		echo(char *command);
void		pwd(char *command);
void		cd(char *command, t_env *env);

/*	----	Exec	----	*/

void		chooser(char *command, t_env *env);

#endif
