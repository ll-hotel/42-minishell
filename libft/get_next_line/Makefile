MAKE		:=	make --no-print-directory
CC			:=	cc

OBJECT_DIR	:=	.obj/

CFLAGS		:=	-Wall -Wextra -Werror
IFLAGS		:=	-I../include

OBJECTS		:=	$(addprefix $(OBJECT_DIR), \
				get_next_line.o \
				get_next_line_utils.o \
				)
DEPS		:=	$(OBJECTS:.o=.d)

NAME		:=	get_next_line.o

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
ifneq ("$(wildcard $(NAME))","")
	rm $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
