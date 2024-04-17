MAKE		:=	@make --no-print-directory
CC			:=	cc

NAME		:=	minishell

INCLUDE_DIR	:=	include/
SOURCE_DIR	:=	src/
OBJECT_DIR	:=	.obj/
LIBFT_DIR	:=	libft/
LIBFT		:=	$(LIBFT_DIR)libft.a

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR)
LFLAGS		:=	-L$(LIBFT_DIR) -lft -lreadline

OBJECTS		:=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
				cutter.c \
				cutter_utils.c \
				display_prompt.c \
				env.c \
				env_var.c \
				free_array.c \
				llst_addback.c \
				llst_clear.c \
				llst_len.c \
				main.c \
				parse_quotes.c \
				token.c \
				welcome.c \
				)
DEPS		:=	$(OBJECTS:.o=.d)

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -maxdepth 1 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(GREEN)
endef

define prompt
	@echo $1"\n================ $2 ================\n"$(END_COLOUR)
endef

define normitest
	@echo $(BLUE)"\nTest norminette..."$(END_COLOUR)
	@if norminette $(SOURCE_DIR) $(INCLUDE_DIR) $(LIBFT_DIR) | grep Error; then \
		echo $(RED)"\n================ Norminette KO ================"$(END_COLOUR); \
	else \
		echo $(GREEN)"\n================ Norminette OK ================"$(END_COLOUR); \
	fi
endef

.PHONY: all clean fclean re

all	:	$(NAME)

-include $(DEPS)

$(NAME)	: 	$(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

$(LIBFT)::
	$(MAKE) -C $(LIBFT_DIR)

$(OBJECT_DIR):
	mkdir $@

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
ifneq ("$(wildcard $(OBJECT_DIR))", "")
	rm -rf $(OBJECT_DIR)
endif

fclean:	clean
	$(MAKE) -C $(LIBFT_DIR) fclean
ifneq ("$(wildcard $(NAME))", "")
	rm -f $(NAME)
endif

re:	fclean
	$(MAKE) all
