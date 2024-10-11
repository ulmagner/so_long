/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 13:10:03 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_player_to_map(t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				i;

	anim = all->player.animation[all->player.i];
	i = all->player.i;
	y = -1;
	while (++y < all->tileset[5][i][anim].h)
	{
		x = -1;
		while (++x < all->tileset[5][i][anim].w)
		{
			color = get_pixel_color(&all->tileset[5][i][anim], x, y);
			ft_pixel_put(&all->game, all->player.x + x,
				all->player.y + y, color);
		}
	}
}

void	copy_oeuil_to_map(t_all *all, t_oeuil *oeuil)
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
			ft_pixel_put(&all->game, oeuil->x + x,
				oeuil->y + y, color);
		}
	}
}

void	copy_slime_to_map(t_all *all, t_slime *slime)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				i;

	anim = slime->anim_slime;
	i = slime->i;
	y = -1;
	while (++y < all->tileset[4][i][anim].h)
	{
		x = -1;
		while (++x < all->tileset[4][i][anim].w)
		{
			color = get_pixel_color(&all->tileset[4][i][anim], x, y);
			ft_pixel_put(&all->game, slime->x + x,
				slime->y + y, color);
		}
	}
}

void	copy_ground_to_map(t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < all->ground.h)
	{
		x = -1;
		while (++x < all->ground.w)
		{
			color = get_pixel_color(&all->ground, x, y);
			ft_pixel_put(&all->game, x,
				y, color);
		}
	}
}

void	copy_trap_to_map(t_all *all, t_trap *trap)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				i;

	anim = trap->anim_trap;
	i = trap->i;
	y = -1;
	while (++y < all->tileset[7][i][anim].h)
	{
		x = -1;
		while (++x < all->tileset[7][i][anim].w)
		{
			color = get_pixel_color(&all->tileset[7][i][anim], x, y);
			ft_pixel_put(&all->game, trap->x + x,
				trap->y + y, color);
		}
	}
}
