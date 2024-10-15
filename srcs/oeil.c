/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oeil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:37:30 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/15 16:15:40 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	move_oeil(t_oeil *oeil, t_map *direction, int axis, t_all *all)
{
	int	new_i;

	new_i = 1;
	oeil->ms = 4;
	if (oeil->o->up == direction || oeil->o->left == direction)
	{
		oeil->ms = -oeil->ms;
		new_i = 0;
	}
	if (direction->i != '1' && direction->i != 'F')
	{
		oeil->i = new_i;
		if (axis == 0)
			if (oeil->y + oeil->ms >= 0 && oeil->y + oeil->ms < all->plan.h)
				oeil->y += oeil->ms;
		if (axis == 1)
			if (oeil->x + oeil->ms >= 0 && oeil->x + oeil->ms < all->plan.w)
				oeil->x += oeil->ms;
		if ((axis == 0 && ((oeil->ms > 0 && oeil->y >= direction->y_pxl) \
			|| (oeil->ms < 0 && oeil->y <= direction->y_pxl))) \
			|| (axis == 1 && ((oeil->ms > 0 && oeil->x >= direction->x_pxl) \
			|| (oeil->ms < 0 && oeil->x <= direction->x_pxl))))
			oeil->o = direction;
	}
}

int	focus(t_all *all, t_oeil *oeil)
{
	if (all->i % 10000 == 0)
		oeil->rd_dir = get_randoms(0, 3, 100);
	if (oeil->rd_dir == 0)
		move_oeil(oeil, oeil->o->up, 0, all);
	else if (oeil->rd_dir == 1)
		move_oeil(oeil, oeil->o->down, 0, all);
	else if (oeil->rd_dir == 2)
		move_oeil(oeil, oeil->o->left, 1, all);
	else if (oeil->rd_dir == 3)
		move_oeil(oeil, oeil->o->right, 1, all);
	return (1);
}

int	movement_handling_oeil(t_all *all, t_oeil *oeil, int i)
{
	get_hitbox_oeil(oeil);
	if (all->dist.p_o[i] <= oeil->reach + all->player.r)
		oeil->focus = true;
	if (all->dist.p_o[i] <= oeil->r + all->player.r && !all->counter.button)
	{
		all->player.is_dead = true;
		all->player.i = 8;
		return (1);
	}
	if (!oeil->focus)
	{
		focus(all, oeil);
		return (1);
	}
	if (oeil->x < all->player.x)
		move_oeil(oeil, oeil->o->right, 1, all);
	else if (oeil->x > all->player.x)
		move_oeil(oeil, oeil->o->left, 1, all);
	if (oeil->y < all->player.y)
		move_oeil(oeil, oeil->o->down, 0, all);
	else if (oeil->y > all->player.y)
		move_oeil(oeil, oeil->o->up, 0, all);
	return (1);
}

void	copy_oeil_plan(t_all *all, t_oeil *oeil)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				i;

	if (all->i % 15000 == 0 && !oeil->is_dead)
	{
		oeil->animation[oeil->i] = (oeil->animation[oeil->i] + 1) % 6;
		oeil->anim = (oeil->anim + 1) % 6;
	}
	anim = oeil->anim;
	i = oeil->i;
	y = -1;
	while (++y < all->tile[6][i][anim].h)
	{
		x = -1;
		while (++x < all->tile[6][i][anim].w)
		{
			color = get_pixel_color(&all->tile[6][i][anim], x, y);
			ft_pixel_put(&all->plan, oeil->x + x,
				oeil->y + y, color);
		}
	}
}
