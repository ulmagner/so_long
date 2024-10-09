/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_oeuil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/09 16:56:03 by ulmagner         ###   ########.fr       */
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

void	move_oeuil(t_oeuil *oeuil, t_map *direction, int new_index, int axis, t_solong *solong)
{
	int	increment;

	if (check_hitbox_player(oeuil->interaction, &solong->player))
	{
		solong->player.is_dead = true;
		solong->player.index = 8;
		return ;
	}
	increment = oeuil->ms;
	if (new_index == 0)
		increment = -increment;
	if (direction->index != '1' && direction->index != 'F')
	{
		oeuil->index = new_index;
		if (axis == 0)
		{
			int new_y = oeuil->y + increment;
			if (new_y >= 0 && new_y < solong->game.height)
				oeuil->y = new_y;
		}
		else if (axis == 1)
		{
			int new_x = oeuil->x + increment;
			if (new_x >= 0 && new_x < solong->game.width)
				oeuil->x = new_x;
		}
		if ((axis == 0 && ((increment > 0 && oeuil->y >= direction->y_pxl) || (increment < 0 && oeuil->y <= direction->y_pxl))) ||
		    (axis == 1 && ((increment > 0 && oeuil->x >= direction->x_pxl) || (increment < 0 && oeuil->x <= direction->x_pxl))))
			oeuil->o = direction;
	}
}

int	movement_handling_oeuil(t_solong *solong, t_oeuil *oeuil)
{
	if (solong->i % 10000 == 0)
		oeuil->rd_dir = get_randoms(0, 3, 100);
	oeuil->ms = 4;
	if (oeuil->rd_dir == 0)
		move_oeuil(oeuil, oeuil->o->up, 0, 0, solong);
	else if (oeuil->rd_dir == 1)
		move_oeuil(oeuil, oeuil->o->down, 1, 0, solong);
	else if (oeuil->rd_dir == 2)
		move_oeuil(oeuil, oeuil->o->left, 0, 1, solong);
	else if (oeuil->rd_dir == 3)
		move_oeuil(oeuil, oeuil->o->right, 1, 1, solong);
	return (1);
}
