/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/03 23:50:49 by ulysse           ###   ########.fr       */
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
			ft_pixel_put(&solong->ground, solong->player.x + x,
				solong->player.y + y, color);
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
			ft_pixel_put(&solong->ground, slime->x + x,
				slime->y + y, color);
		}
	}
}
