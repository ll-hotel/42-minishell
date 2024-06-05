MAKE		=	@make --no-print-directory
ECHO		=	echo
CC			=	cc

NAME		=	minishell

INCLUDE_DIR	=	include/
SOURCE_DIR	=	src/
OBJECT_DIR	=	.obj/
LIBFT_DIR	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a

CFLAGS		=	-Wall -Wextra -Werror
IFLAGS		=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR)
DFLAGS		=	-MMD -MP
LFLAGS		=	-L$(LIBFT_DIR) -lft -lreadline

ifneq ("$(DEBUG)", "")
CFLAGS += $(DEBUG)
endif

OBJECTS		=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
				builtins/chooser.c \
				builtins/msh_cd.c \
				builtins/msh_echo.c \
				builtins/msh_env.c \
				builtins/msh_exit.c \
				builtins/msh_export.c \
				builtins/msh_pwd.c \
				builtins/msh_unset.c \
				core/env.c \
				core/main.c \
				core/msh_status.c \
				core/signal_gestionnary.c \
				exec/exec_find_command.c \
				exec/exec_one.c \
				exec/exec_open_redirects.c \
				exec/exec_path.c \
				exec/exec_pipeline.c \
				exec/exec_utils.c \
				exec/msh_exec.c \
				llst/command.c \
				llst/env_var.c \
				llst/llst_addback.c \
				llst/llst_addfront.c \
				llst/llst_at.c \
				llst/llst_clear.c \
				llst/llst_delone.c \
				llst/llst_get_last.c \
				llst/llst_len.c \
				llst/llst_next.c \
				llst/token.c \
				parsing/command_creator.c \
				parsing/env_var_expand.c \
				parsing/lexer_append.c \
				parsing/lexer_dollar.c \
				parsing/lexer_dquote.c \
				parsing/lexer_line.c \
				parsing/lexer_redir.c \
				parsing/lexer_utils.c \
				parsing/lexer_word.c \
				parsing/msh_parser.c \
				parsing/parse_dquote.c \
				parsing/parse_redir.c \
				parsing/split_env_vars.c \
				parsing/expand_env_vars.c \
				parsing/msh_syntax_err.c \
				parsing/syntax_checker.c \
				utils/display_prompt.c \
				utils/ft_close.c \
				utils/ft_free.c \
				utils/ft_free_parray.c \
				utils/welcome.c \
				)
DEPS		=	$(OBJECTS:.o=.d)

NB_FILES = $(words $(OBJECTS))
GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@$(ECHO) -n $(GREEN)"[$$(echo "scale=2; $$(find $(OBJECT_DIR) -maxdepth 3 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(END_COLOUR)
endef

define prompt
	@$(ECHO) $1"\n================ $2 ================\n"$(END_COLOUR)
endef

define normitest
	@$(ECHO) $(BLUE)"\nTest norminette..."$(END_COLOUR)
	@if norminette $(SOURCE_DIR) $(INCLUDE_DIR) $(LIBFT_DIR) | grep Error; then \
		$(ECHO) $(RED)"\n================ Norminette KO ================"$(END_COLOUR); \
	else \
		$(ECHO) $(GREEN)"\n================ Norminette OK ================"$(END_COLOUR); \
	fi
endef

.PHONY: all
all	:	$(NAME)

-include $(DEPS)

$(NAME)	: 	$(LIBFT) $(OBJECTS)
	@$(call percent)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

$(LIBFT)::
	$(MAKE) -C $(LIBFT_DIR)

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	@$(call percent)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p $@builtins/
	mkdir -p $@core/
	mkdir -p $@exec/
	mkdir -p $@llst/
	mkdir -p $@parsing/
	mkdir -p $@utils/	

.PHONY: clean
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
ifneq ("$(wildcard $(OBJECT_DIR))", "")
	rm -rf $(OBJECT_DIR)
endif

.PHONY: fclean
fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
ifneq ("$(wildcard $(NAME))", "")
	rm -f $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
