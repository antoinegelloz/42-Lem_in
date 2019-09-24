# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 10:17:32 by agelloz           #+#    #+#              #
#    Updated: 2019/09/24 14:34:16 by agelloz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = Clang
CFLAGS = -Wall -Wextra
#CFLAGS = -Wall -Wextra -g3 -fsanitize=address,undefined -Wpadded
CLEANUP = /bin/rm -rf
INC = libft.h
INC_DIR = inc/
OBJ_DIR = obj/

vpath %.c src/lists
vpath %.c src/other
vpath %.c src/printing
vpath %.c src/strings
vpath %.c src/printf
vpath %.h inc/

SRC += float_aux.c
SRC += float_calc.c
SRC += float_calc_string.c
SRC += float_calc_string2.c
SRC += float_format.c
SRC += formatting.c
SRC += initialize.c
SRC += parsing.c
SRC += print_address.c
SRC += print_char.c
SRC += print_error.c
SRC += print_float.c
SRC += print_octal.c
SRC += print_percent.c
SRC += print_signed_base.c
SRC += print_string.c
SRC += print_unsigned_base.c
SRC += printf.c
SRC += ft_memalloc.c
SRC += ft_memccpy.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_memcpy.c
SRC += ft_memdel.c
SRC += ft_memmove.c
SRC += ft_memset.c
SRC += ft_delcontent.c
SRC += ft_cpycontent.c
SRC += ft_ascending_order.c
SRC += ft_descending_order.c
SRC += ft_bzero.c
SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isdigit.c
SRC += ft_isprint.c
SRC += ft_strcat.c
SRC += ft_strchr.c
SRC += ft_strclr.c
SRC += ft_strcmp.c
SRC += ft_strcpy.c
SRC += ft_strdel.c
SRC += ft_strdup.c
SRC += ft_strdupfree.c
SRC += ft_strequ.c
SRC += ft_striter.c
SRC += ft_striteri.c
SRC += ft_strjoin.c
SRC += ft_strjoin_free.c
SRC += ft_strlcat.c
SRC += ft_strlen.c
SRC += ft_strmap.c
SRC += ft_strmapi.c
SRC += ft_strncat.c
SRC += ft_strncmp.c
SRC += ft_strncpy.c
SRC += ft_strnequ.c
SRC += ft_strnew.c
SRC += ft_strnstr.c
SRC += ft_strrchr.c
SRC += ft_strsplit.c
SRC += ft_strstr.c
SRC += ft_strsub.c
SRC += ft_strtrim.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_atoi.c
SRC += ft_atol.c
SRC += ft_itoa.c
SRC += ft_putchar.c
SRC += ft_putchar_fd.c
SRC += ft_putendl.c
SRC += ft_putendl_fd.c
SRC += ft_putnbr.c
SRC += ft_putnbr_fd.c
SRC += ft_putstr.c
SRC += ft_putstr_fd.c
SRC += ft_lstnew.c
SRC += ft_lstadd.c
SRC += ft_lstprepend.c
SRC += ft_lstappend.c
SRC += ft_lstdel.c
SRC += ft_lstdelone.c
SRC += ft_lstiter.c
SRC += ft_lstsorted.c
SRC += ft_lstswap.c
SRC += ft_lstpush.c
SRC += ft_lstrotate.c
SRC += ft_lstrevrotate.c
SRC += ft_lstcount.c
SRC += ft_lstcpy.c
SRC += ft_lstncpy.c
SRC += ft_lstrev.c
SRC += ft_lstgetmin.c
SRC += ft_lstgetmax.c
SRC += ft_lstindex.c
SRC += ft_lst_mergesort.c
SRC += get_next_line.c

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	ar -rsc $@ $^
	printf "$(GREEN)created: $@\n$(NC)"

$(OBJ): $(OBJ_DIR)%.o : %.c $(INC)
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@
	printf "$(CYAN)compiling: $<\n$(NC)"

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(CLEANUP) $(OBJ)
	$(CLEANUP) $(OBJ_DIR)
	#printf "$(RED)objects removed from libft\n$(NC)"

fclean: clean
	$(CLEANUP) $(NAME)
	printf "$(RED)deleted: $(NAME)\n$(NC)"

re: fclean all

CYAN=\033[0;36m
BLUE=\033[0;34m
GREEN=\033[32m
RED=\033[0;31m
WHITE=\033[0;37m
PURPLE=\033[0;35m
YELLOW=\033[0;33m
NC=\033[0m

.PHONY: all clean fclean re
.SILENT:
