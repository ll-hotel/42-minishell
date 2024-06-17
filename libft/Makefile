MAKE = @make --no-print-directory
ECHO = echo
CC = cc
CFLAGS = -Wall -Wextra -Werror
ifneq ("$(DEBUG)", "")
CFLAGS += $(DEBUG)
endif
IFLAGS = -Iinclude/
DFLAGS = -MMD -MP

OBJ_DIR = .obj
BASICS_OBJS = $(patsubst %.c,$(OBJ_DIR)/basics/%.o, \
			  ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
			  ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			  ft_itoa_base.c ft_itoa.c ft_log_b.c ft_lstadd_back_bonus.c \
			  ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
			  ft_lstdelone_bonus.c ft_lstiter_bonus.c \
			  ft_lstlast_bonus.c ft_lstmap_bonus.c \
			  ft_lstnew_bonus.c ft_lstsize_bonus.c \
			  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			  ft_putstr.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			  ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			  ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
			  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			  ft_tolower.c ft_toupper.c ft_utoa.c \
			  )

FT_PRINTF_OBJS = $(patsubst %.c,$(OBJ_DIR)/ft_printf/%.o, \
				 ft_printf.c ft_printf_handlers.c ft_printf_xtoa.c)				 

GNL_OBJS = $(patsubst %.c,$(OBJ_DIR)/get_next_line/%.o, \
		   lrichaud-get_next_line.c)
		   #get_next_line.c get_next_line_utils.c)

VECTOR_OBJS = $(patsubst %.c,$(OBJ_DIR)/vector/%.o, \
			  vector_addback.c vector_at.c vector_clear.c vector_new.c vector_del_at.c)

FT_DPRINTF_OBJS = $(patsubst %.c,$(OBJ_DIR)/ft_dprintf/%.o, \
				  dprintf_ascii.c dprintf_atoi32.c dprintf_atoi64.c dprintf_buffer.c \
				  dprintf.c dprintf_specifier.c dprintf_utils.c)

EXTRA_OBJS = $(patsubst %.c,${OBJ_DIR}/extra/%.o, \
			 ft_realloc.c \
			 ft_strichr.c \
			 ft_isspace.c \
			 ft_isblank.c \
			 ft_memdup.c \
			 ft_min.c \
			 ft_splat.c \
			 ft_strcmp.c \
			 ft_strtok.c)

OBJS = ${BASICS_OBJS} ${FT_PRINTF_OBJS} ${GNL_OBJS} ${VECTOR_OBJS} ${FT_DPRINTF_OBJS} ${EXTRA_OBJS}

DEPS = $(patsubst %.o,%.d,${OBJS})

NAME = libft.a

.PHONY: all
all: ${NAME}

-include ${DEPS}

.SILENT: ${NAME}
${NAME}: ${OBJS}
	ar -rc $@ ${OBJS}
	${ECHO} "\e[33mLibft:  Done!\e[0m"

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
	${CC} ${CFLAGS} ${IFLAGS} ${DFLAGS} -o $@ -c $<

${OBJ_DIR}:
	mkdir -p $(sort $(dir ${OBJS}))

.SILENT: clean
.PHONY: clean
clean:
ifneq ("$(wildcard ${OBJ_DIR})", "")
	rm -rf ${OBJ_DIR}
	echo "Libft:  Object file directory removed"
endif

.SILENT: fclean
.PHONY: fclean
fclean: clean
ifneq ("$(wildcard ${NAME})", "")
	rm -f ${NAME}
	echo "Libft:  ${NAME} removed"
endif

.SILENT: re
.PHONY: re
re:	fclean
	${MAKE} all
