# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 12:05:17 by ulmagner          #+#    #+#              #
#    Updated: 2024/10/11 11:08:00 by ulmagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

BONUS_NAME	= so_long_bonus

LFT_NAME	= libft.a

MLX_NAME	= libmlx.a

SRCS		= main.c error_handling.c map_handling.c free.c lst.c get_info.c \
map_xpm.c tileset.c mouvement.c launcher.c clear.c player.c get_path.c \
action.c direction.c mouvement_oeuil.c slime.c trap.c hitbox.c hooks.c \
get_textures.c get_textures_bis.c build_image.c fog.c \

SRCS_B		= main_bonus.c \

INCS		= solong.h
INCS_B		= allb.h
INCS_LFT	= libft.h
INCS_MLX	= mlx.h
SDIRS		= srcs
SDIRS_B		= srcsb
IDIRS		= includes
IDIRS_B		= includesb
IDIRS_LFT	= includes/libfts/includes
IDIRS_MLX	= includes/minilibx-linux
ODIRS		= objs
ODIRS_B		= objs_b
DIRS_LFT	= includes/libfts
DIRS_MLX	= includes/minilibx-linux

IFILES		= $(addprefix $(IDIRS)/,$(INCS))
IFILES_B	= $(addprefix $(IDIRS)/,$(INCS))
IFILES_LFT	= $(addprefix $(IDIRS_LFT)/,$(INCS_LFT))
IFILES_MLX	= $(addprefix $(IDIRS_MLX)/,$(INCS_MLX))
SFILES		= $(addprefix $(SDIRS)/,$(SRCS))
SFILES_B	= $(addprefix $(SDIRS_B)/,$(SRCS_B))
OFILES		= $(addprefix $(ODIRS)/,$(patsubst %.c,%.o,$(SRCS)))
OFILES_B	= $(addprefix $(ODIRS_B)/,$(patsubst %.c,%.o,$(SRCS_B)))
A_LFT		= $(addprefix $(DIRS_LFT)/,$(LFT_NAME))
A_MLX		= $(addprefix $(DIRS_MLX)/,$(MLX_NAME))

CC			= cc -O3 -ggdb
MLX_FLAGS	= -lXext -lX11 -lz -lm -pthread -ldl -lpthread -lXfixes -lasound
CFLAGS		= -Wall -Wextra -Werror -std=c99
OPTION		= -I$(IDIRS) -I$(IDIRS_LFT) -I$(IDIRS_MLX)
MAKEFLAGS 	+= -s
MAKE		= make

all:	$(NAME)

$(ODIRS):
	@mkdir -p $(ODIRS)

$(ODIRS)/%.o: $(SDIRS)/%.c $(IFILES) $(IFILES_LFT) $(IFILES_MLX) | $(ODIRS)
	$(CC) -DMANDATORY=1 $(CFLAGS) $(OPTION) -c $< -o $@

$(A_LFT):
	$(MAKE) -C $(DIRS_LFT)

$(A_MLX):
	$(MAKE) -C $(DIRS_MLX)

$(NAME): $(OFILES) $(A_LFT) $(A_MLX)
	$(CC) -o $(NAME) $(CFLAGS) $(OPTION) $(OFILES) $(A_LFT) $(A_MLX) $(MLX_FLAGS)

bonus:	$(BONUS_NAME)

$(ODIRS_B):
	@mkdir -p $(ODIRS_B)

$(ODIRS_B)/%.o: $(SDIRS_B)/%.c $(IFILES) $(IFILES_LFT) $(IFILES_MLX) | $(ODIRS_B)
	$(CC) $(CFLAGS) $(OPTION) -c $< -o $@

$(BONUS_NAME): $(OFILES_B) $(A_LFT) $(A_MLX)
	$(CC) -o $(BONUS_NAME) $(CFLAGS) $(OPTION) $(OFILES_B) $(A_LFT) $(A_MLX) $(MLX_FLAGS)

clean:
	rm -f $(OFILES) $(OFILES_B)
	@rm -rf $(ODIRS) $(ODIRS_B)
	$(MAKE) -C $(DIRS_LFT) clean
	# $(MAKE) -C $(DIRS_MLX) clean

fclean:	clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MAKE) -C $(DIRS_LFT) fclean

re: fclean all

.PHONY: all bonus fclean clean re
