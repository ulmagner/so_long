/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/27 15:20:13 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_player_to_map(t_solong *solong, int index)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < solong->tileset[5][solong->player.index][index].height)
	{
		x = -1;
		while (++x < solong->tileset[5][solong->player.index][index].width)
		{
			color = get_pixel_color(&solong->tileset[5][solong->player.index][index], x, y);
			ft_pixel_put(&solong->ground, \
				solong->player.x + x, \
				solong->player.y + y, \
				color);
		}
	}
}
