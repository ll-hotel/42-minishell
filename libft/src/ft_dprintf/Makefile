MAKE			:=	@make --no-print-directory
        		
DEBUG			:=	
CC				:=	cc
SOURCE_DIR		:=	src/
OBJECT_DIR		:=	.obj/
CFLAGS			:=	-Wall -Wextra -Werror
IFLAGS			:=	-I./
INCLUDES		:=	ft_dprintf.h src/dprintf_inner.h
OBJECTS			:=	$(patsubst %.c,$(OBJECT_DIR)%.o, \
					dprintf_ascii.c dprintf_atoi32.c dprintf_atoi64.c \
					dprintf_buffer.c dprintf.c dprintf_specifier.c \
					dprintf_utils.c \
					)

DEPENDENCIES	:=	Makefile $(INCLUDES)
NAME			:=	ft_dprintf.o

.PHONY : all clean fclean re

all: $(NAME)

$(OBJECT_DIR):
	mkdir $(OBJECT_DIR)

$(NAME)		: $(OBJECT_DIR) $(OBJECTS) $(DEPENDENCIES)
	ld -relocatable -o $@ $(OBJECTS)

$(OBJECT_DIR)%.o 	: $(SOURCE_DIR)%.c $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
ifneq ("$(wildcard $(OBJECT_DIR))","")
	rm -rf $(OBJECT_DIR)
endif

fclean:	clean
ifneq ("$(wildcard $(NAME))","")
	rm $(NAME)
endif

re:	fclean all
