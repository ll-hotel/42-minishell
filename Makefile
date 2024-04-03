MAKE		:=	@make --no-print-directory
CC			:=	cc

INCLUDE_DIR	:=	include/
SOURCE_DIR	:=	src/
OBJECT_DIR	:=	.obj/

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I$(INCLUDE_DIR)
LFLAGS		:=	-Llibft -lft

OBJECTS		:=	$(patsubst %.c,$(OBJECT_DIR)%.o, main.c)
DEPS		:=	$(OBJECTS:.o=.d)

NAME		:=	minishell

.PHONY: all clean fclean re

all	:	$(NAME)

-include $(DEPS)

$(NAME)	:	libft $(OBJECTS)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

libft::
	$(MAKE) -C libft

$(OBJECT_DIR):
	mkdir $@

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJECT_DIR)

fclean:	clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re:	fclean
	$(MAKE) all
