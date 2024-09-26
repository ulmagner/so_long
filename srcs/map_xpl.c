/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:09:50 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 13:14:05 by ulmagner         ###   ########.fr       */
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

void	copy_tile_to_map(t_image *image, t_image *ground, t_map *map)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
		{
			color = get_pixel_color(image, \
				0 * image->width + x, 0 * image->height + y);
			ft_pixel_put(ground, \
				map->x * image->width + x, map->y * image->height + y, color);
		}
	}
}

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
			color = get_pixel_color(&solong->tileset[5][0], \
				0 * solong->tileset[5][0].width + x, 0 * solong->tileset[5][0].height + y);
			ft_pixel_put(&solong->ground, \
				solong->player.hero->x * solong->tileset[5][0].width + x, solong->player.hero->y * solong->tileset[5][0].height + y, color);
		}
	}
}

void	build_map(t_solong *solong)
{
	t_map	*col;

	col = solong->map;
	while (col)
	{
		copy_tile_to_map(&solong->tileset[0][0], &solong->ground, col);
		if (col->index == '1' && col->y == solong->info.nbr_line - 1)
			copy_tile_to_map(&solong->tileset[1][0], &solong->ground, col);
		else if (col->index == '1' && col->x == 0)
			copy_tile_to_map(&solong->tileset[1][3], &solong->ground, col);
		else if (col->index == '1' && col->y == 0)
			copy_tile_to_map(&solong->tileset[1][2], &solong->ground, col);
		else if (col->index == '1' && col->x == solong->info.nbr_column - 1)
			copy_tile_to_map(&solong->tileset[1][1], &solong->ground, col);
		else if (col->index == '1')
			copy_tile_to_map(&solong->tileset[2][0], &solong->ground, col);
		if (col->index == 'E' && col->down->index == '0')
			copy_tile_to_map(&solong->tileset[3][0], &solong->ground, col);
		if (col->index == 'C')
			copy_tile_to_map(&solong->tileset[4][0], &solong->ground, col);
		// if (col->index == 'P')
		// 	copy_tile_to_map(&solong->tileset[5][0], &solong->ground, col);
		col = col->right;
	}
}
