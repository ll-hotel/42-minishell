MAKE			:=	make --no-print-directory
CC				:=	cc

CFLAGS			:=	$(DEBUG) -Wall -Wextra -Werror
IFLAGS			:=	-I./

OBJECTS_DIR		:=	.obj/
SOURCES_DIR		:=	src/
DPRINTF_DIR		:=	$(SOURCES_DIR)ft_dprintf/

INCLUDES		:=	libft.h \
					$(addprefix $(SOURCES_DIR), \
					basics.h get_next_line.h \
					) \
					$(DPRINTF_DIR)ft_dprintf.h 


FT_DPRINTF		:=	$(DPRINTF_DIR)ft_dprintf.o

OBJECTS			:=	$(patsubst %.c,$(OBJECTS_DIR)%.o, \
					ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
					ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_log_b.c \
					ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c \
					ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c \
					ft_lstsize_bonus.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c \
					ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c \
					ft_putstr_fd.c ft_realloc.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
					ft_tolower.c ft_toupper.c ft_utoa.c \
					ft_printf.c ft_printf_handlers.c ft_printf_xtoa.c \
					get_next_line.c get_next_line_utils.c \
					vector_new.c vector_at.c vector_addback.c vector_clear.c \
					) \
					$(FT_DPRINTF)
NAME			:=	libft.a

.PHONY:	all clean fclean re

all				:	$(NAME)

$(NAME)			:	Makefile $(INCLUDES) $(OBJECTS_DIR) $(OBJECTS)
	ar -rc $@ $(OBJECTS)

$(OBJECTS_DIR)%.o	:	$(SOURCES_DIR)%.c Makefile $(INCLUDES)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(FT_DPRINTF)		:
	@$(MAKE) -C $(DPRINTF_DIR)

$(OBJECTS_DIR)	:
	mkdir $@

clean:
	@$(MAKE) -C $(DPRINTF_DIR) clean
	rm -rf $(OBJECTS_DIR)

fclean:	clean
	@$(MAKE) -C $(DPRINTF_DIR) fclean
	rm -f $(NAME)

re:	fclean
	@$(MAKE) all
