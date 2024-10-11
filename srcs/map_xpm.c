/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:09:50 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 17:27:28 by ulmagner         ###   ########.fr       */
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

void	copy_to_map(t_image *image, t_image *ground, t_map *map)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			color = get_pixel_color(image, \
				0 * image->w + x, 0 * image->h + y);
			ft_pixel_put(ground, \
				map->x * image->w + x, map->y * image->h + y, color);
		}
	}
}

void	copy_game_map(t_image *image, t_image *bg, t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;

	(void) all;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			color = get_pixel_color(image, \
				0 * image->w + x, 0 * image->h + y);
			ft_pixel_put(bg, x + ((bg->w / 2) - (image->w / 2)), \
				y + ((bg->h / 2) - (image->h / 2)), color);
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
