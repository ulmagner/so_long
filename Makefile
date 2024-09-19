# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 12:05:17 by ulmagner          #+#    #+#              #
#    Updated: 2024/09/19 15:28:45 by ulmagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

BONUS_NAME	= so_long_bonus

LIB_NAME	= libft.a

SRCS		= main.c error_handling.c map_handling.c \

SRCS_LIB	= ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c \
ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c	ft_strrchr.c \
ft_strstr.c	ft_tolower.c ft_toupper.c ft_atoi.c	ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_bzero.c ft_strlcpy.c \
ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_isstrchr.c ft_countwords.c \
ft_split.c ft_strjoin.c ft_itoa.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putnbr_fd.c ft_putendl_fd.c ft_strtrim.c ft_strmapi.c ft_substr.c \
ft_striteri.c ft_strnstr.c ft_lstlast.c ft_lstsize.c ft_lstnew.c ft_lstmap.c \
ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
ft_printf.c ft_printf_utils.c ft_printf_utils_bis.c ft_get_next_line.c \

SRCS_B		= main_bonus.c \

INCS		= solong.h
INCS_B		= solongb.h
INCS_LIB	= libft.h

SDIRS		= srcs
SDIRS_B		= srcsb
SDIRS_LIB	= libfts/srcs
IDIRS		= includes
IDIRS_B		= includesb
IDIRS_LIB	= libfts/includes
ODIRS		= $(SDIRS)
ODIRS_B		= $(SDIRS_B)
ODIRS_LIB	= libobj

IFILES		= $(addprefix $(IDIRS)/,$(INCS))
IFILES_B	= $(addprefix $(IDIRS)/,$(INCS))
IFILES_LIB	= $(addprefix $(IDIRS_LIB)/,$(INCS))
SFILES		= $(addprefix $(SDIRS)/,$(SRCS))
SFILES_B	= $(addprefix $(SDIRS_B)/,$(SRCS_B))
SFILES_LIB	= $(addprefix $(SDIRS_LIB)/,$(SRCS_LIB))
OFILES		= $(patsubst %.c,%.o,$(SFILES))
OFILES_B	= $(patsubst %.c,%.o,$(SFILES_B))
OFILES_LIB	= $(addprefix $(ODIRS_LIB)/,$(patsubst %.c,%.o,$(SRCS_LIB)))

CFLAGS		= -Wall -Wextra -Werror -ggdb -std=c99 -I$(IDIRS) -I$(IDIRS_LIB)
MAKEFLAGS 	+= -s

all: $(NAME)

$(ODIRS)/%.o: $(SDIRS)/%.c $(IFILES) $(IFILES_LIB)
	@mkdir -p $(ODIRS)
	$(CC) $(CFLAGS) -I$(IDIRS) -I(IDIRS_LIB) -c $< -o $@

$(ODIRS_LIB)/%.o: $(SDIRS_LIB)/%.c
	@mkdir -p $(ODIRS_LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(OFILES_LIB)
	ar rcs $@ $^

$(NAME): $(OFILES) $(LIB_NAME)
	cc $(CFLAGS) $(OFILES) -L. -lft -o $(NAME)

bonus:	$(BONUS_NAME)

$(ODIRS_B)/%.o: $(SDIRS_B)/%.c $(IFILES) $(IFILES_LIB)
	@mkdir -p $(ODIRS_B)
	$(CC) $(CFLAGS) -I$(IDIRS) -I$(IDIRS_LIB) -c $< -o $@

$(ODIRS_LIB)/%.o: $(SDIRS_LIB)/%.c
	@mkdir -p $(ODIRS_LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME): $(OFILES_B) $(LIB_NAME)
	cc $(CFLAGS) $(OFILES_B) -L. -lft -o $(BONUS_NAME)

clean:
	rm -f $(OFILES) $(OFILES_B) $(OFILES_LIB)
	@rm -rf $(ODIRS_LIB)

fclean:	clean
	rm -f $(NAME)
	rm -f $(LIB_NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all bonus fclean clean re
