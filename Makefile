MAKE		:=	@make --no-print-directory
ECHO		:=	echo -e
CC			:=	cc

NAME		:=	minishell

INCLUDE_DIR	:=	include/
SOURCE_DIR	:=	src/
OBJECT_DIR	:=	.obj/
LIBFT_DIR	:=	libft/
LIBFT		:=	$(LIBFT_DIR)libft.a

CFLAGS		=	-Wall -Wextra -Werror
IFLAGS		:=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR)
DFLAGS		:=	-MMD -MP
LFLAGS		:=	-L$(LIBFT_DIR) -lft -lreadline

ifneq ("$(DEBUG)", "")
CFLAGS += $(DEBUG)
endif

OBJECTS		:=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
				cd.c \
				chooser.c \
				cutter.c \
				cutter_utils.c \
				command.c \
				command_creator.c \
				display_prompt.c \
				echo.c \
				env.c \
				env_var.c \
				free_array.c \
				ft_free.c \
				grammary_checker.c \
				lexer_on_cuts.c \
				lexer_utils.c \
				llst_addback.c \
				llst_clear.c \
				llst_delone.c \
				llst_get_last.c \
				llst_len.c \
				main.c \
				pwd.c \
				token.c \
				welcome.c \
				)
DEPS		:=	$(OBJECTS:.o=.d)

NB_FILES = $(words $(OBJECTS))
GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@$(ECHO) -n $(GREEN)"[$$(echo "scale=2; $$(find $(OBJECT_DIR) -maxdepth 1 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(END_COLOUR)
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
	mkdir $@

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	@$(call percent)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(MAKE) -sC $(LIBFT_DIR) clean
ifneq ("$(wildcard $(OBJECT_DIR))", "")
	rm -rf $(OBJECT_DIR)
endif

.PHONY: fclean
fclean:	clean
	$(MAKE) -sC $(LIBFT_DIR) fclean
ifneq ("$(wildcard $(NAME))", "")
	rm -f $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
