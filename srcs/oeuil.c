/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oeuil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/13 23:02:38 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_oeuil(t_oeuil *oeuil, t_map *direction, int axis, t_all *all)
{
	int	new_i;

	new_i = 1;
	if (oeuil->o->up == direction || oeuil->o->left == direction)
	{
		oeuil->ms = -oeuil->ms;
		new_i = 0;
	}
	if (direction->i != '1' && direction->i != 'F')
	{
		oeuil->i = new_i;
		if (axis == 0)
		{
			if (oeuil->y + oeuil->ms >= 0 && oeuil->y + oeuil->ms < all->plan.h)
				oeuil->y += oeuil->ms;
		}
		else if (axis == 1)
			if (oeuil->x + oeuil->ms >= 0 && oeuil->x + oeuil->ms < all->plan.w)
				oeuil->x += oeuil->ms;
		if ((axis == 0 && ((oeuil->ms > 0 && oeuil->y >= direction->y_pxl) \
			|| (oeuil->ms < 0 && oeuil->y <= direction->y_pxl))) \
			|| (axis == 1 && ((oeuil->ms > 0 && oeuil->x >= direction->x_pxl) \
			|| (oeuil->ms < 0 && oeuil->x <= direction->x_pxl))))
			oeuil->o = direction;
	}
}

int	movement_handling_oeuil(t_all *all, t_oeuil *oeuil, int i)
{
	if (all->i % 10000 == 0)
		oeuil->rd_dir = get_randoms(0, 3, 100);
	oeuil->ms = 4;
	if (all->dist.p_o[i] <= oeuil->r + all->player.r && !all->counter.button)
	{
		all->player.is_dead = true;
		all->player.i = 8;
		return (1);
	}
	if (oeuil->rd_dir == 0)
		move_oeuil(oeuil, oeuil->o->up, 0, all);
	else if (oeuil->rd_dir == 1)
		move_oeuil(oeuil, oeuil->o->down, 0, all);
	else if (oeuil->rd_dir == 2)
		move_oeuil(oeuil, oeuil->o->left, 1, all);
	else if (oeuil->rd_dir == 3)
		move_oeuil(oeuil, oeuil->o->right, 1, all);
	return (1);
}

void	copy_oeuil_plan(t_all *all, t_oeuil *oeuil)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				i;

	if (all->i % 15000 == 0 && !oeuil->is_dead)
	{
		oeuil->animation[oeuil->i] = (oeuil->animation[oeuil->i] + 1) % 6;
		oeuil->anim = (oeuil->anim + 1) % 6;
	}
	anim = oeuil->anim;
	i = oeuil->i;
	y = -1;
	while (++y < all->tileset[6][i][anim].h)
	{
		x = -1;
		while (++x < all->tileset[6][i][anim].w)
		{
			color = get_pixel_color(&all->tileset[6][i][anim], x, y);
			ft_pixel_put(&all->plan, oeuil->x + x,
				oeuil->y + y, color);
		}
	}
}
