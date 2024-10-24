/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:09:50 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:31:28 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_to_ground(t_image *image, t_image *ground, t_map *map)
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
			color = get_pixel_color(image, x, y);
			ft_pixel_put(ground, \
				map->x * image->w + x, map->y * image->h + y, color);
		}
	}
}

void	copy_countdowns(t_image *image, t_image *ground, int off, int y_ref)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w - off - 12)
		{
			color = get_pixel_color(image, x, y);
			ft_pixel_put(ground, \
				50 + x, y_ref + y, color);
		}
	}
}

void	copy_to_game(t_image *image, t_image *ground, int x_ref, int y_ref)
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
			color = get_pixel_color(image, x, y);
			ft_pixel_put(ground, \
				(x_ref) + x, (y_ref) + y, color);
		}
	}
}

void	copy_to_view(t_image *image, t_image *bg, t_view *view, t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;

	(void) all;
	(void) view;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			color = get_pixel_color(image, x, y);
			ft_pixel_put(bg, x + bg->w / 2 - image->w / 2, \
				y + bg->h / 2 - image->h / 2, color);
		}
	}
}
