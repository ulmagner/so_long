/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_oeuil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/07 12:12:56 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_oeuil(t_solong *solong, t_map *direction, int new_index, int axis)
{
	int	increment;

	increment = solong->oeuil.ms;
	if (new_index == 0)
		increment = -increment;
	if (direction->index != '1')
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
	}
}

int	movement_handling_oeuil(t_solong *solong)
{
	if (solong->i % 10 != 0)
		return (0);
	if (solong->i % 100 == 0)
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
