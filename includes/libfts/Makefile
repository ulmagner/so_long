# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 10:05:18 by ulmagner          #+#    #+#              #
#    Updated: 2024/09/20 10:19:13 by ulmagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	=	ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c \
ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c	ft_strrchr.c \
ft_strstr.c	ft_tolower.c ft_toupper.c ft_atoi.c	ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_bzero.c ft_strlcpy.c \
ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_isstrchr.c ft_countwords.c \
ft_split.c ft_strjoin.c ft_itoa.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putnbr_fd.c ft_putendl_fd.c ft_strtrim.c ft_strmapi.c ft_substr.c \
ft_striteri.c ft_strnstr.c ft_lstlast.c ft_lstsize.c ft_lstnew.c ft_lstmap.c \
ft_lstadd_front.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
ft_printf.c ft_printf_utils.c ft_printf_utils_bis.c ft_get_next_line.c \

INCS	= libft.h

SDIRS	= srcs
IDIRS	= includes
ODIRS	= objs

SFILES	= $(addprefix $(SDIRS)/,$(SRCS))
IFILES	= $(addprefix $(IDIRS)/,$(INCS))
OFILES	= $(addprefix $(ODIRS)/,$(patsubst %.c,%.o,$(SRCS)))

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -ggdb -std=c99
MAKEFLAGS += -s

all: $(NAME)

$(ODIRS):
	@mkdir -p $(ODIRS)

$(ODIRS)/%.o: $(SDIRS)/%.c $(IFILES) | $(ODIRS)
	$(CC) $(CFLAGS) -c -I$(IDIRS) $< -o $@

$(NAME): $(OFILES)
	ar -rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)
	rm -rf $(ODIRS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all so fclean clean re 
