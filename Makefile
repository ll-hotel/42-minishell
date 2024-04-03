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
				main.c \
				display_prompt.c\
				)
DEPS		:=	$(OBJECTS:.o=.d)

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
