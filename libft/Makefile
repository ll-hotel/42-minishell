MAKE			:=	@make --no-print-directory
CC				:=	cc

CFLAGS			:=	$(DEBUG) -Wall -Wextra -Werror
IFLAGS			:=	-I./ -Iinclude/

OBJECT_DIR		:=	.obj/
SOURCE_DIR		:=	src/

PRINTF_DIR		:=	ft_printf/
DPRINTF_DIR		:=	ft_dprintf/
GNL_DIR			:=	get_next_line/
VECTOR_DIR		:=	vector/

FT_PRINTF		:=	$(PRINTF_DIR)ft_printf.o
FT_DPRINTF		:=	$(DPRINTF_DIR)ft_dprintf.o
GET_NEXT_LINE	:=	$(GNL_DIR)get_next_line.o
VECTOR			:=	$(VECTOR_DIR)vector.o

OBJECTS			:=	$(patsubst %.c, $(OBJECT_DIR)%.o, \
					ft_atoi.c \
					ft_bzero.c \
					ft_calloc.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_itoa.c \
					ft_log_b.c \
					ft_lstadd_back_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstnew_bonus.c \
					ft_lstsize_bonus.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr.c \
					ft_putstr_fd.c \
					ft_realloc.c \
					ft_split.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlcpy.c \
					ft_strlen.c \
					ft_strmapi.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strtrim.c \
					ft_substr.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_utoa.c \
					) \
					$(FT_PRINTF) \
					$(FT_DPRINTF) \
					$(GET_NEXT_LINE) \
					$(VECTOR)

DEPS			:=	$(patsubst %.o, %.d, $(OBJECTS))

NAME			:=	libft.a

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rc $@ $(OBJECTS)

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(FT_PRINTF)::
	$(MAKE) -C $(PRINTF_DIR)

$(FT_DPRINTF)::
	$(MAKE) -C $(DPRINTF_DIR)

$(GET_NEXT_LINE)::
	$(MAKE) -C $(GNL_DIR)

$(VECTOR)::
	$(MAKE) -C $(VECTOR_DIR)

$(OBJECT_DIR):
	mkdir $@

.PHONY: clean
clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(DPRINTF_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(VECTOR_DIR) clean
	@rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean:	clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(DPRINTF_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(VECTOR_DIR) fclean
ifneq ("$(wildcard $(NAME))", "")
	rm -rf $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
