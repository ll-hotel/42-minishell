MAKE			:=	@make --no-print-directory
CC				:=	cc

SOURCE_DIR		:=	src/
OBJECT_DIR		:=	.obj/
INCLUDE_DIR		:=	include/

CFLAGS			:=	-Wall -Wextra -Werror
IFLAGS			:=	-I$(INCLUDE_DIR) -I../include

OBJECTS			:=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
					dprintf.c \
					dprintf_ascii.c \
					dprintf_atoi32.c \
					dprintf_atoi64.c \
					dprintf_buffer.c \
					dprintf_specifier.c \
					dprintf_utils.c \
					)
DEPS			:= $(patsubst %.o,%.d, $(OBJECTS))

NAME			:=	ft_dprintf.o

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(NAME)		: $(OBJECTS)
	ld -relocatable -o $@ $(OBJECTS)

$(OBJECT_DIR)%.o 	: $(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir $@

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
