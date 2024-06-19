/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniChell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:39:36 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/20 00:59:52 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINICHELL_H
# define MINICHELL_H
# include "libft.h"
# include "llst.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# include <wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/*	----	TYPEDEFS	----	*/

typedef struct s_evar		t_evar;
typedef struct s_miniChell	t_ch;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;

enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_SQUOTE,
	TOKEN_DQUOTE,
	TOKEN_ENV_VAR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_PIPE,
	TOKEN_SPACE,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
};

enum	e_open_flags
{
	REDIR_OUT_FLAGS = (O_CREAT | O_WRONLY | O_TRUNC),
	APPEND_FLAGS = (O_CREAT | O_WRONLY | O_APPEND),
	FILE_PERMS = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH),
};

/*	----	STRUCT		----	*/

struct	s_miniChell
{
	t_llst_head	evars;
	t_llst_head	args;
	t_llst_head	cmds;
};

struct	s_evar
{
	t_evar	*next;
	char	*name;
	char	*value;
};

struct	s_token
{
	t_token		*next;
	char		*str;
	t_llst_head	inner_tokens;
	int			fd;
	int			type;
};

struct	s_cmd
{
	t_cmd		*next;
	t_llst_head	redirs;
	int			fd_in;
	int			fd_out;
	char		**path;
	char		*executable;
	int			argc;
	char		**argv;
	char		**envp;
};

/*	----	ENVIRONMENT	----	*/

int		ch_env_init(t_ch *ch, char *const *envp);
int		ch_insert_evar(t_evar *evar_head, t_evar *evar);
t_evar	*find_evar(t_ch *ch, char *name);
char	**ch_to_array(t_evar *evar_head);
int		evar_expand(t_llst_head *evar, t_ch *ch);
t_evar	*evar_new(char *p);
void	evar_free(void *var);
void	free_ch(t_ch *ch);

/*	----	TOKEN	----	*/

t_token	*token_new(void *str, int type);
void	token_free(void *token);

/*	----	LEXER	----	*/

t_token	*lexer_line(char *line);
t_token	*lexer_word(char *line, int *p_i);
t_token	*lexer_dollar(char *line, int *p_i);
t_token	*lexer_simple_quote(char *line, int *p_i);
t_token	*lexer_dquote(char *line, int *p_i);
t_token	*lexer_redir(char *line, int *p_i);
t_token	*lexer_append(char *line, int *p_i);
int		is_operator(int c);
t_token	*lexer_heredoc(char *line, int *p_i);

/*	----	PARSER	----	*/

int		ch_parser(t_llst_head *token_lst, t_ch *ch);
int		expand_evars(t_token *head, t_ch *ch);
int		split_evars(t_token *head);
int		parse_dquote(t_token *head, t_ch *ch);
void	parse_redir(t_token *head);
int		check_redir_validity(t_token *head);
int		parser_heredoc(t_token *head, t_ch *ch);
int		heredoc_expand(t_ch *ch, int hd_input, int *hd_expanded);

/*	----	SYNTAX	----	*/

void	ch_syntax_err(char c);

/*	----	COMMAND		----	*/

t_cmd	*cmd_creator(t_llst_head *tokenlst_head);
void	cmd_free(void *cmd);

/*	----	UTILS	----	*/

void	welcome_test_subject(void);
char	*display_prompt(void);
void	*ft_free(void *p);
int		ft_close(int fd);
void	ft_free_parray(void *array);
void	ft_free_array(void *array);
int		ft_is_number(char *str);
void	closer(t_cmd *cmd);

/*	----	Builtins	----	*/

int		chooser(t_cmd *cmd, t_ch *ch);
int		ch_echo(t_cmd *cmd);
int		ch_pwd(t_ch *ch);
int		ch_cd(t_cmd *cmd, t_ch *ch);
int		ch_env(t_cmd *cmd, t_ch *ch);
void	ch_exit(t_ch *ch, int status);
int		ch_export(t_cmd *cmd, t_ch *ch);
int		ch_unset(t_cmd *cmd, t_ch *ch);
int		exit_error_checker(t_ch *ch, t_cmd *cmd);

/*	----	Exec	----	*/

void	ch_exec(t_ch *ch);
int		exec_pipeline(t_ch *ch);
int		exec_one(t_ch *ch, t_cmd *cmd);
int		exec_open_redirs(t_cmd *cmd);
char	**exec_get_path(t_ch *ch);
int		exec_find_cmd(t_cmd *cmd, char **path);
int		exec_dup2(t_cmd *cmd);
void	exec_perror_exit(t_ch *ch, int status);
int		exec_wait_children(int last_pid);

/*	----	Status	----	*/

uint8_t	ch_status_set(uint8_t value);
uint8_t	ch_status_get(void);
uint8_t	ch_status_get_error(void);

/*	----	Signal	----	*/

void	signal_gestionnary(void);

#endif
