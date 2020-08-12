# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agelloz <agelloz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 10:17:32 by agelloz           #+#    #+#              #
#    Updated: 2019/12/02 13:49:14 by agelloz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
################################                ################################
################################ MAIN VARIABLES ################################
################################                ################################
################################################################################

# Name
NAME = libft.a

# Compiler
CC = clang

# Compiler Flags
CFLAGS += -Wall
CFLAGS += -Wextra

# Compiler Debug Flags
ifeq ($(d), 0)
	CFLAGS += -g3
else ifeq ($(d), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(d), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
else ifeq ($(d), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
else ifeq ($(d), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Wpadded
	CFLAGS += -pedantic
	CFLAGS += -Weverything
endif
ifneq ($(err), no)
	CFLAGS += -Werror
endif

# Debug Dir
DSYM += $(NAME).dSYM
DSYM += $(DBNAME).dSYM

################################################################################
################################                ################################
################################   PRINT VAR    ################################
################################                ################################
################################################################################

# Reset
NC = \033[0m

# Regular Colors
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m

# One Line Output
ONELINE =\e[1A\r

################################################################################
#################################               ################################
#################################    INCLUDES   ################################
#################################               ################################
################################################################################

INCLUDES_LIBFT = inc/

I_INCLUDES += -I $(INCLUDES_LIBFT)

################################################################################
#################################               ################################
#################################    HEADERS    ################################
#################################               ################################
################################################################################

# libft
HEADER += libft.h

# ft_printf
HEADER += printf.h
HEADER += printf_floats.h

vpath %.h $(INCLUDES_LIBFT)

################################################################################
#################################               ################################
#################################  PATH SOURCES ################################
#################################               ################################
################################################################################

PATH_SRCS = src/
PATH_SRCS_PRINTF = src/printf/

################################################################################
#################################               ################################
#################################    SOURCES    ################################
#################################               ################################
################################################################################

SRCS += float_aux.c
SRCS += float_calc.c
SRCS += float_calc_string.c
SRCS += float_calc_string2.c
SRCS += float_format.c
SRCS += formatting.c
SRCS += initialize.c
SRCS += parsing.c
SRCS += print_address.c
SRCS += print_char.c
SRCS += print_error.c
SRCS += print_float.c
SRCS += print_octal.c
SRCS += print_percent.c
SRCS += print_signed_base.c
SRCS += print_string.c
SRCS += print_unsigned_base.c
SRCS += printf.c
SRCS += ft_memalloc.c
SRCS += ft_memccpy.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_memcpy.c
SRCS += ft_memdel.c
SRCS += ft_memmove.c
SRCS += ft_memset.c
SRCS += ft_delcontent.c
SRCS += ft_cpycontent.c
SRCS += ft_ascending_order.c
SRCS += ft_descending_order.c
SRCS += ft_bzero.c
SRCS += ft_isalnum.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_isprint.c
SRCS += ft_strcat.c
SRCS += ft_strchr.c
SRCS += ft_strclr.c
SRCS += ft_strcmp.c
SRCS += ft_strcpy.c
SRCS += ft_strdel.c
SRCS += ft_strdup.c
SRCS += ft_strdupfree.c
SRCS += ft_strequ.c
SRCS += ft_striter.c
SRCS += ft_striteri.c
SRCS += ft_strjoin.c
SRCS += ft_strjoin_free.c
SRCS += ft_strlcat.c
SRCS += ft_strlen.c
SRCS += ft_strmap.c
SRCS += ft_strmapi.c
SRCS += ft_strncat.c
SRCS += ft_strncmp.c
SRCS += ft_strncpy.c
SRCS += ft_strnequ.c
SRCS += ft_strnew.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strsplit.c
SRCS += ft_strstr.c
SRCS += ft_strsub.c
SRCS += ft_strtrim.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c
SRCS += ft_atoi.c
SRCS += ft_atol.c
SRCS += ft_itoa.c
SRCS += ft_putchar.c
SRCS += ft_putchar_fd.c
SRCS += ft_putendl.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putstr.c
SRCS += ft_putstr_fd.c
SRCS += ft_lstnew.c
SRCS += ft_lstadd.c
SRCS += ft_lstprepend.c
SRCS += ft_lstappend.c
SRCS += ft_lstdel.c
SRCS += ft_lstdelone.c
SRCS += ft_lstiter.c
SRCS += ft_lstsorted.c
SRCS += ft_lstswap.c
SRCS += ft_lstpush.c
SRCS += ft_lstrotate.c
SRCS += ft_lstrevrotate.c
SRCS += ft_lstcount.c
SRCS += ft_lstcpy.c
SRCS += ft_lstncpy.c
SRCS += ft_lstrev.c
SRCS += ft_lstgetmin.c
SRCS += ft_lstgetmax.c
SRCS += ft_lstgetsize.c
SRCS += ft_lstindex.c
SRCS += ft_lst_mergesort.c
SRCS += get_next_line.c


################# ATTRIBUTION

vpath %.c $(PATH_SRCS)
vpath %.c $(PATH_SRCS_PRINTF)

################################################################################
#################################               ################################
#################################    OBJECTS    ################################
#################################               ################################
################################################################################

PATH_OBJS = obj/
OBJS = $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

################################################################################
#################################               ################################
#################################     RULES     ################################
#################################               ################################
################################################################################

#---------------------------------- Standard ----------------------------------#

all: $(PATH_OBJS) $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(I_INCLUDES) -c $< -o $@
	printf "$(CYAN)compiling $<\n"

$(PATH_OBJS):
	mkdir $@

#--------------------------------- Basic Rules --------------------------------#

clean:
	$(RM) $(OBJS)
	$(RM) -R $(PATH_OBJS)
	$(RM) -R $(DSYM)
	printf "$(RED)objs from libft removed\n$(NC)"

fclean: clean
	$(RM) $(NAME)
	printf "$(RED)$(NAME) removed\n$(NC)"

re: fclean
	$(MAKE)

#----------------------------------- Special ----------------------------------#

.PHONY: clean fclean re all
.SILENT:
