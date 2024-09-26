/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 19:21:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_player_to_map(t_solong *solong)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < solong->tileset[5][0].height)
	{
		x = -1;
		while (++x < solong->tileset[5][0].width)
		{
			color = get_pixel_color(&solong->tileset[5][0], x, y);
			ft_pixel_put(&solong->ground, \
				solong->player.hero->x_pxl + x, \
				solong->player.hero->y_pxl + y, \
				color);
		}
	}
}
