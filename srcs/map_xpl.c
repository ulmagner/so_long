/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:09:50 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 11:17:32 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr \
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	char	*src;

	src = image->addr \
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

void	copy_tile_to_map(t_solong *solong, int tile_x, int tile_y, t_map *map)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			color = get_pixel_color(&solong->tileset, \
				tile_x * TILE_SIZE + x, tile_y * TILE_SIZE + y);
			ft_pixel_put(&solong->ground, \
				map->x * TILE_SIZE + x, map->y * TILE_SIZE + y, color);
		}
	}
}

void	build_map(t_solong *solong)
{
	t_map	*col;

	col = solong->map;
	while (col)
	{
		copy_tile_to_map(solong, 0, 0, col);
		col = col->right;
	}
}
