MAKE		:=	make --no-print-directory
CC			:=	cc

OBJECT_DIR	:=	.obj/

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I../include

OBJECTS		:=	$(patsubst %.c, $(OBJECT_DIR)%.o, \
				vector_addback.c \
				vector_at.c \
				vector_clear.c \
				vector_new.c \
				)
DEPS		:=	$(OBJECTS:.o=.d)

NAME		:=	vector.o

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS)
	ld -relocatable -o $@ $(OBJECTS)

$(OBJECT_DIR):
	mkdir $@

$(OBJECT_DIR)%.o: %.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

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
