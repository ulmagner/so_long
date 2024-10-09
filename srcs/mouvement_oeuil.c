/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_oeuil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/09 12:39:57 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_hitbox_player(int interaction[4][2], t_player *player)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	while (++i < 4)
	{
		x = interaction[i][0];
		y = interaction[i][1];
		if (x >= player->x && x <= player->x + 64 \
			&& y >= player->y && y <= player->y + 64)
			return (1);
	}
	return (0);
}

void	move_oeuil(t_solong *solong, t_map *direction, int new_index, int axis)
{
	int	increment;

	increment = solong->oeuil.ms;
	if (new_index == 0)
		increment = -increment;
	if (direction->index != '1' && direction->index != 'F')
	{
		solong->oeuil.index = new_index;
		if (axis == 0)
		{
			int new_y = solong->oeuil.y + increment;
			if (new_y >= 0 && new_y < solong->game.height)
				solong->oeuil.y = new_y;
		}
		else if (axis == 1)
		{
			int new_x = solong->oeuil.x + increment;
			if (new_x >= 0 && new_x < solong->game.width)
				solong->oeuil.x = new_x;
		}
		if ((axis == 0 && ((increment > 0 && solong->oeuil.y >= direction->y_pxl) || (increment < 0 && solong->oeuil.y <= direction->y_pxl))) ||
		    (axis == 1 && ((increment > 0 && solong->oeuil.x >= direction->x_pxl) || (increment < 0 && solong->oeuil.x <= direction->x_pxl))))
			solong->oeuil.o = direction;
		if (check_hitbox_player(solong->oeuil.interaction, &solong->player))
		{
			ft_printf(2, "oeuil:[%d:%d] player:[%d:%d]\n", solong->oeuil.o->x_pxl, solong->oeuil.o->y_pxl, solong->player.hero->x_pxl, solong->player.hero->y_pxl);
			solong->player.is_dead = true;
			solong->player.index = 8;
		}
	}
}

int	movement_handling_oeuil(t_solong *solong)
{
	if (solong->i % 10000 == 0)
		solong->oeuil.rd_dir = get_randoms(0, 3, 100);
	solong->oeuil.ms = 4;
	if (solong->oeuil.rd_dir == 0)
		move_oeuil(solong, solong->oeuil.o->up, 0, 0);
	else if (solong->oeuil.rd_dir == 1)
		move_oeuil(solong, solong->oeuil.o->down, 1, 0);
	else if (solong->oeuil.rd_dir == 2)
		move_oeuil(solong, solong->oeuil.o->left, 0, 1);
	else if (solong->oeuil.rd_dir == 3)
		move_oeuil(solong, solong->oeuil.o->right, 1, 1);
	return (1);
}
