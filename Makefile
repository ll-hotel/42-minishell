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
				chooser.c \
				command.c \
				command_creator.c \
				display_prompt.c \
				env.c \
				env_var.c \
				env_var_expand.c \
				ft_close.c \
				ft_free.c \
				ft_free_parray.c \
				lexer_line.c \
				lexer_utils.c \
				lexer_word.c \
				lexer_dollar.c \
				lexer_dquote.c \
				lexer_redir.c \
				llst_addback.c \
				llst_addfront.c \
				llst_at.c \
				llst_clear.c \
				llst_delone.c \
				llst_get_last.c \
				llst_len.c \
				llst_next.c \
				main.c \
				msh_cd.c \
				msh_echo.c \
				msh_env.c \
				msh_exec.c \
				msh_exec_command.c \
				msh_exec_one.c \
				msh_exec_open_redirections.c \
				msh_exec_path.c \
				msh_exec_pipeline.c \
				msh_exit.c \
				msh_export.c \
				msh_parser.c \
				msh_pwd.c \
				msh_syntax_err.c \
				msh_unset.c \
				syntax_checker.c \
				token.c \
				welcome.c \
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

$(OBJECT_DIR):
	mkdir -p $@

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	@$(call percent)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

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
