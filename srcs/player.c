/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 15:57:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_player_to_map(t_solong *solong)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				index;

	anim = solong->player.animation[solong->player.index];
	index = solong->player.index;
	y = -1;
	while (++y < solong->tileset[5][index][anim].height)
	{
		x = -1;
		while (++x < solong->tileset[5][index][anim].width)
		{
			color = get_pixel_color(&solong->tileset[5][index][anim], x, y);
			ft_pixel_put(&solong->game, solong->player.x + x,
				solong->player.y + y, color);
		}
	}
}

void	copy_oeuil_to_map(t_solong *solong, t_oeuil *oeuil)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				index;

	if (solong->i % 15000 == 0 && !oeuil->is_dead)
	{
		oeuil->animation[oeuil->index] = (oeuil->animation[oeuil->index] + 1) % 6;
		oeuil->anim = (oeuil->anim + 1) % 6;
	}
	anim = oeuil->anim;
	index = oeuil->index;
	y = -1;
	while (++y < solong->tileset[6][index][anim].height)
	{
		x = -1;
		while (++x < solong->tileset[6][index][anim].width)
		{
			color = get_pixel_color(&solong->tileset[6][index][anim], x, y);
			ft_pixel_put(&solong->game, oeuil->x + x,
				oeuil->y + y, color);
		}
	}
}

void	copy_slime_to_map(t_solong *solong, t_slime *slime)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				index;

	anim = slime->anim_slime;
	index = slime->index;
	y = -1;
	while (++y < solong->tileset[4][index][anim].height)
	{
		x = -1;
		while (++x < solong->tileset[4][index][anim].width)
		{
			color = get_pixel_color(&solong->tileset[4][index][anim], x, y);
			ft_pixel_put(&solong->game, slime->x + x,
				slime->y + y, color);
		}
	}
}

void	copy_ground_to_map(t_solong *solong)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < solong->ground.height)
	{
		x = -1;
		while (++x < solong->ground.width)
		{
			color = get_pixel_color(&solong->ground, x, y);
			ft_pixel_put(&solong->game, x,
				y, color);
		}
	}
}

void	copy_trap_to_map(t_solong *solong, t_trap *trap)
{
	unsigned int	color;
	int				x;
	int				y;
	int				anim;
	int				index;

	anim = trap->anim_trap;
	index = trap->index;
	y = -1;
	while (++y < solong->tileset[7][index][anim].height)
	{
		x = -1;
		while (++x < solong->tileset[7][index][anim].width)
		{
			color = get_pixel_color(&solong->tileset[7][index][anim], x, y);
			ft_pixel_put(&solong->game, trap->x + x,
				trap->y + y, color);
		}
	}
}
