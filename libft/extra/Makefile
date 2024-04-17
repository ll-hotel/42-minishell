MAKE		:=	make --no-print-directory
CC			:=	cc

OBJECT_DIR	:=	.obj/

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I../include/

OBJECTS		:=	$(patsubst %.c, $(OBJECT_DIR)%.o, \
				ft_realloc.c \
				)
DEPS		:=	$(OBJECTS:.o=.d)

NAME		:=	extra.o

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS)
	ld -relocatable -o $@ $(OBJECTS)

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir $@

.PHONY: clean
clean:
ifneq ("$(wildcard $(OBJECT_DIR))", "")
	@rm -rf $(OBJECT_DIR)
endif

.PHONY: fclean
fclean:	clean
ifneq ("$(wildcard $(NAME))", "")
	rm $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
