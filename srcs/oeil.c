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

void	update_pos(int axis, t_map *direction, int new_i, t_oeil *oeil)
{
	if ((axis == 0 && ((oeil->ms > 0 && oeil->y >= direction->y_pxl)
				|| (oeil->ms < 0 && oeil->y <= direction->y_pxl)))
		|| (axis == 1 && ((oeil->ms > 0 && oeil->x >= direction->x_pxl)
				|| (oeil->ms < 0 && oeil->x <= direction->x_pxl))))
	{
		oeil->o = direction;
		oeil->i = new_i;
	}
}

void	move_oeil(t_oeil *oeil, t_map *direction, int axis, t_all *all)
{
	int	new_i;

	new_i = 1;
	if (direction->i == '1' || direction->i == 'F')
		return ;
	if (oeil->o->up == direction || oeil->o->left == direction)
	{
		if (oeil->ms > 0)
			oeil->ms = -oeil->ms;
		new_i = 0;
	}
	else if (oeil->ms < 0)
			oeil->ms = -oeil->ms;
	if (axis == 0 && (oeil->y + oeil->ms >= 0 \
		&& oeil->y + oeil->ms < all->plan.h))
		oeil->y += oeil->ms;
	else if (axis == 1 && (oeil->x + oeil->ms >= 0 \
		&& oeil->x + oeil->ms < all->plan.w))
		oeil->x += oeil->ms;
	update_pos(axis, direction, new_i, oeil);
}

int	focus(t_all *all, t_oeil *oeil)
{
	if (all->i - oeil->frameoeil >= (int)(1000 / 60))
	{
		oeil->rd_dir = get_randoms(0, 3, 100);
		oeil->frameoeil = all->i;
	}
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

int	movement_handling_oeil(t_all *all, t_oeil *oeil, int k)
{
	oeil->ms = 2;
	if (oeil->is_dead || oeil->is_stun)
		return (1);
	if (all->dist.p_o[k] <= oeil->reach + all->player.r)
	{
		oeil->focus = true;
		oeil->ms = 4;
	}
	if (all->dist.p_o[k] <= oeil->r + all->player.r)
	{
		all->player.is_dead = true;
		all->player.i = 8;
		return (1);
	}
	if (!oeil->focus)
		return (focus(all, oeil));
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

	if (all->i - oeil->frameoeill >= (int)(200 / 60) && !oeil->is_dead)
	{
		oeil->anim = (oeil->anim + 1) % 6;
		oeil->frameoeill = all->i;
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
