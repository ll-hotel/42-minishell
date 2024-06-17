MAKE		=	make --no-print-directory
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
				builtins/ch_cd.c \
				builtins/ch_echo.c \
				builtins/ch_env.c \
				builtins/ch_exit.c \
				builtins/ch_export.c \
				builtins/ch_pwd.c \
				builtins/ch_unset.c \
				core/env.c \
				core/main.c \
				core/ch_status.c \
				core/signal_gestionnary.c \
				exec/exec_find_cmd.c \
				exec/exec_one.c \
				exec/exec_open_redirects.c \
				exec/exec_path.c \
				exec/exec_pipeline.c \
				exec/exec_utils.c \
				exec/ch_exec.c \
				llst/cmd.c \
				llst/evar.c \
				llst/llst_addback.c \
				llst/llst_addfront.c \
				llst/llst_at.c \
				llst/llst_clear.c \
				llst/llst_delone.c \
				llst/llst_get_last.c \
				llst/llst_len.c \
				llst/llst_next.c \
				llst/token.c \
				parsing/cmd_creator.c \
				parsing/evar_expand.c \
				parsing/heredoc_expand.c \
				parsing/lexer_append.c \
				parsing/lexer_dollar.c \
				parsing/lexer_dquote.c \
				parsing/lexer_heredoc.c \
				parsing/lexer_line.c \
				parsing/lexer_redir.c \
				parsing/lexer_utils.c \
				parsing/lexer_word.c \
				parsing/ch_parser.c \
				parsing/parse_dquote.c \
				parsing/parse_redir.c \
				parsing/parser_heredoc.c \
				parsing/split_evars.c \
				parsing/expand_evars.c \
				parsing/ch_syntax_err.c \
				utils/display_prompt.c \
				utils/ft_close.c \
				utils/ft_free.c \
				utils/ft_free_parray.c \
				)
DEPS		=	$(OBJECTS:.o=.d)

NB_FILES = $(words $(OBJECTS))
GREEN='\e[0;32m'
RED='\e[0;31m'
BLUE='\e[0;34m'
END_COLOUR='\e[0m'

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
all	:	${NAME}

-include ${DEPS}

${NAME}	: 	${LIBFT} ${OBJECTS}
	@$(call percent)
	${CC} ${CFLAGS} ${IFLAGS} ${DFLAGS} -o $@ ${OBJECTS} ${LFLAGS}

.SILENT: ${LIBFT}
${LIBFT}::
	${MAKE} -C ${LIBFT_DIR}

${OBJECT_DIR}%.o:	${SOURCE_DIR}%.c | ${OBJECT_DIR}
	@$(call percent)
	${CC} ${CFLAGS} ${IFLAGS} ${DFLAGS} -o $@ -c $<

${OBJECT_DIR}:
	mkdir -p $(sort $(dir ${OBJECTS}))

.PHONY: clean
clean:
	${MAKE} -C ${LIBFT_DIR} clean
ifneq ("$(wildcard ${OBJECT_DIR})", "")
	rm -rf ${OBJECT_DIR}
endif

.PHONY: fclean
fclean:	clean
	${MAKE} -C ${LIBFT_DIR} fclean
ifneq ("$(wildcard ${NAME})", "")
	rm -f ${NAME}
endif

.SILENT: re
.PHONY: re
re:	fclean
	${MAKE} all
