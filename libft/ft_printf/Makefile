MAKE		:=	make --no-print-directory
CC			:=	cc

SOURCE_DIR	:=	./
OBJECT_DIR	:=	.obj/

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I../include
LFLAGS		:=

OBJECTS		:=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
				ft_printf.c \
				ft_printf_handlers.c \
				ft_printf_xtoa.c)

DEPS		:=	$(OBJECTS:.o=.d)

NAME		:=	ft_printf.o

.PHONY: all
all	:	$(NAME)

-include $(DEPS)

$(NAME)	:	$(OBJECTS)
	ld -relocatable -o $@ $(OBJECTS)

$(OBJECT_DIR):
	mkdir $@

$(OBJECT_DIR)%.o:	$(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean:	clean
ifneq ("$(wildcard $(NAME))", "")
	rm $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
