/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/05/28 19:50:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "llst.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <wait.h>
# define EXIT_OUT_OF_MEMORY 12
# define EXIT_BROKEN_PIPE 32
# define EXIT_CMD_NOT_FOUND 127

/*	----	TYPEDEFS	----	*/

typedef struct s_env_var	t_env_var;
typedef struct s_env		t_env;
typedef struct s_minishell	t_msh;
typedef struct s_token		t_token;
typedef struct s_command	t_command;

enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_SIMPLE_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_ENV_VAR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_PIPE,
	TOKEN_SPACE,
};

/*	----	STRUCT		----	*/

struct	s_env
{
	t_llst_head	vars;
	int			last_exit_status;
};

struct	s_minishell
{
	t_env		env;
	t_llst_head	args;
	t_llst_head	cmds;
	t_vec		children;
};

struct	s_env_var
{
	t_env_var	*next;
	char		*name;
	char		*value;
};

struct	s_token
{
	t_token	*next;
	union
	{
		char		*str;
		t_llst_head	inner_tokens;
	};
	int		type;
};

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
	char		**envp;
};

/*	----	ENVIRONMENT	----	*/

int			env_init(t_env *env, char *const *envp);
t_env_var	*env_var_get(t_env *env, char *name);
char		**env_to_array(t_env *env);
int			env_var_expand(t_llst_head *env_var, t_env *env);
t_env_var	*env_var_new(char *p);
void		env_var_free(void *var);
void		free_env(t_env *env);

/*	----	TOKEN	----	*/

t_token		*token_new(void *str, int type);
void		token_free(void *token);

/*	----	LEXER	----	*/

t_token		*lexer_line(char *line);
t_token		*lexer_word(char *line, int *p_i);
t_token		*lexer_dollar(char *line, int *p_i);
t_token		*lexer_simple_quote(char *line, int *p_i);
t_token		*lexer_dquote(char *line, int *p_i);
t_token		*lexer_redir(char *line, int *p_i);
//t_token		*lexer_double_quote(char *line, int *p_i);
int			is_operator(int c);

/*	----	PARSER	----	*/

int			msh_parser(t_llst_head *token_lst, t_env *env);

/*	----	SYNTAX_CHECKER	----	*/

int			syntax_checker(t_token *token);
void		msh_syntax_err(char c);

/*	----	COMMAND		----	*/

t_command	*command_creator(t_llst_head *tokenlst_head);
void		command_free(void *command);

/*	----	UTILS	----	*/

void		welcome_test_subject(void);
char		*display_prompt(void);
void		*ft_free(void *p);
int			ft_close(int fd);
void		ft_free_parray(void *array);
void		ft_free_array(void *array);

/*	----	Builtins	----	*/

int			chooser(t_command *cmd, t_msh *msh);
int			msh_echo(t_command *cmd);
int			msh_pwd(t_command *cmd);
int			msh_cd(t_command *cmd, t_env *env);
int			msh_env(t_command *cmd, t_env *env);
int			msh_export(t_command *cmd, t_env *env);
int			msh_unset(t_command *cmd, t_env *env);
void		msh_exit(t_msh *msh, int status);

/*	----	Exec	----	*/

int			msh_exec(t_msh *msh, t_command *cmd);
int			msh_exec_pipeline(t_msh *msh, t_command *cmd);
int			msh_exec_one(t_msh *msh, t_command *cmd);
int			msh_exec_open_redirections(t_command *cmd);
char		**msh_exec_get_path(t_env *env);
int			msh_exec_find_command(t_command *cmd, char **path);

int			exec_dup2(t_command *cmd);
int			exec_wait_for_children(t_msh *msh);
void		exec_kill_children(t_msh *msh);
void		exec_perror_exit(t_msh *msh, int status);

#endif
