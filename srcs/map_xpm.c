/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:09:50 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/08 19:45:37 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	dst = image->addr \
		+ (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	char	*src;

	src = image->addr \
		+ ((y * image->line_length) + (x * image->bits_per_pixel / 8));
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

int	get_randoms(int min, int max, int count)
{
	int	i;
	int	rd_num;

	i = -1;
	rd_num = -1;
	while (++i < count)
		rd_num = rand() % (max - min + 1) + min;
	return (rd_num);
}

void	deco_management(t_solong *solong, t_deco *deco, t_map **col)
{
	if ((*col)->index == 'C' && (*col)->is_visited == 2)
		copy_tile_to_map(&solong->tileset[2][0][deco->anim_jar], \
			&solong->ground, *col);
	if ((*col)->index == 'C' && (*col)->is_visited != 2)
		copy_tile_to_map(&solong->tileset[2][0][0], &solong->ground, *col);
}

void	build_map(t_solong *solong)
{
	t_map	*col;
	int		i;

	i = -1;
	col = solong->map;
	while (col)
	{
		if (++i % 2 == 0)
			copy_tile_to_map(&solong->tileset[0][0][0], &solong->ground, col);
		else
			copy_tile_to_map(&solong->tileset[0][0][1], &solong->ground, col);
		if ((col->index == '1' || col->index == 'F') && col->y == 0)
		{
			if (col->x == 0)
				solong->wall.anim = 0;
			else
				solong->wall.anim = (solong->wall.anim + 1) % 3;
			copy_tile_to_map(&solong->tileset[1][0][solong->wall.anim], &solong->ground, col);
		}
		else if ((col->index == '1' || col->index == 'F') && col->y == solong->info.nbr_line - 1)
			copy_tile_to_map(&solong->tileset[1][1][0], &solong->ground, col);
		else if ((col->index == '1' || col->index == 'F') && col->x == 0)
			copy_tile_to_map(&solong->tileset[1][2][0], &solong->ground, col);
		else if ((col->index == '1' || col->index == 'F') && col->x == solong->info.nbr_column - 1)
			copy_tile_to_map(&solong->tileset[1][3][0], &solong->ground, col);
		else if (col->index == '1' || col->index == 'F')
			copy_tile_to_map(&solong->tileset[2][1][0], &solong->ground, col);
		if (col->index == '1' && col->x == 0 && col->y == 0)
			copy_tile_to_map(&solong->tileset[1][4][0], &solong->ground, col);
		if (col->index == '1' && col->x == 0 && col->y == solong->info.nbr_line - 1)
			copy_tile_to_map(&solong->tileset[1][4][2], &solong->ground, col);
		if (col->index == '1' && col->x == solong->info.nbr_column - 1 && col->y == 0)
			copy_tile_to_map(&solong->tileset[1][4][1], &solong->ground, col);
		if (col->index == '1' && col->x == solong->info.nbr_column - 1 && col->y == solong->info.nbr_line - 1)
			copy_tile_to_map(&solong->tileset[1][4][3], &solong->ground, col);
		deco_management(solong, &solong->deco, &col);
		if (col->index == 'E' && solong->info.exit)
			copy_tile_to_map(&solong->tileset[3][0][0], &solong->ground, col);
		col = col->right;
	}
}

void	build_game(t_solong *solong)
{
	t_map	*col;

	col = solong->map;
	while (col)
	{
		deco_management(solong, &solong->deco, &col);
		if (col->index == 'E' && solong->info.exit)
			copy_tile_to_map(&solong->tileset[3][0][0], &solong->ground, col);
		col = col->right;
	}
}
