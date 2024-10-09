/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_oeuil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_oeuil(t_oeuil *oeuil, t_map *direction, int new_i, int axis, t_all *all)
{
	int	increment;

	if (check_hitbox_player(oeuil->interaction, &all->player))
	{
		all->player.is_dead = true;
		all->player.i = 8;
		return ;
	}
	increment = oeuil->ms;
	if (new_i == 0)
		increment = -increment;
	if (direction->i != '1' && direction->i != 'F')
	{
		oeuil->i = new_i;
		if (axis == 0)
		{
			int new_y = oeuil->y + increment;
			if (new_y >= 0 && new_y < all->game.height)
				oeuil->y = new_y;
		}
		else if (axis == 1)
		{
			int new_x = oeuil->x + increment;
			if (new_x >= 0 && new_x < all->game.width)
				oeuil->x = new_x;
		}
		if ((axis == 0 && ((increment > 0 && oeuil->y >= direction->y_pxl) || (increment < 0 && oeuil->y <= direction->y_pxl))) ||
		    (axis == 1 && ((increment > 0 && oeuil->x >= direction->x_pxl) || (increment < 0 && oeuil->x <= direction->x_pxl))))
			oeuil->o = direction;
	}
}

int	movement_handling_oeuil(t_all *all, t_oeuil *oeuil)
{
	if (all->i % 10000 == 0)
		oeuil->rd_dir = get_randoms(0, 3, 100);
	oeuil->ms = 4;
	if (oeuil->rd_dir == 0)
		move_oeuil(oeuil, oeuil->o->up, 0, 0, all);
	else if (oeuil->rd_dir == 1)
		move_oeuil(oeuil, oeuil->o->down, 1, 0, all);
	else if (oeuil->rd_dir == 2)
		move_oeuil(oeuil, oeuil->o->left, 0, 1, all);
	else if (oeuil->rd_dir == 3)
		move_oeuil(oeuil, oeuil->o->right, 1, 1, all);
	return (1);
}
