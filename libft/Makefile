MAKE			:=	@make --no-print-directory
CC				:=	cc

CFLAGS			:=	$(DEBUG) -Wall -Wextra -Werror
IFLAGS			:=	-I./ -Iinclude/

BASICS_DIR		:=	basics/
PRINTF_DIR		:=	ft_printf/
DPRINTF_DIR		:=	ft_dprintf/
GNL_DIR			:=	get_next_line/
VECTOR_DIR		:=	vector/
EXTRA_DIR		:=	extra/

BASICS			:=	$(BASICS_DIR)basics.o
FT_PRINTF		:=	$(PRINTF_DIR)ft_printf.o
FT_DPRINTF		:=	$(DPRINTF_DIR)ft_dprintf.o
GET_NEXT_LINE	:=	$(GNL_DIR)get_next_line.o
VECTOR			:=	$(VECTOR_DIR)vector.o
EXTRA			:=	$(EXTRA_DIR)extra.o

OBJECTS			:=	$(BASICS) \
					$(FT_PRINTF) \
					$(FT_DPRINTF) \
					$(GET_NEXT_LINE) \
					$(VECTOR) \
					$(EXTRA)

DEPS			:=	$(patsubst %.o, %.d, $(OBJECTS))

NAME			:=	libft.a

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rc $@ $(OBJECTS)

$(BASICS)::
	$(MAKE) -C $(BASICS_DIR)

$(FT_PRINTF)::
	$(MAKE) -C $(PRINTF_DIR)

$(FT_DPRINTF)::
	$(MAKE) -C $(DPRINTF_DIR)

$(GET_NEXT_LINE)::
	$(MAKE) -C $(GNL_DIR)

$(VECTOR)::
	$(MAKE) -C $(VECTOR_DIR)

$(EXTRA)::
	$(MAKE) -C $(EXTRA_DIR)

$(OBJECT_DIR):
	mkdir $@

.PHONY: clean
clean:
	$(MAKE) -C $(BASICS_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(DPRINTF_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(VECTOR_DIR) clean
	$(MAKE) -C $(EXTRA_DIR) clean
	@rm -rf $(OBJECT_DIR)

.PHONY: fclean
fclean:	clean
	$(MAKE) -C $(BASICS_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(DPRINTF_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(VECTOR_DIR) fclean
	$(MAKE) -C $(EXTRA_DIR) fclean
ifneq ("$(wildcard $(NAME))", "")
	rm $(NAME)
endif

.PHONY: re
re:	fclean
	$(MAKE) all
