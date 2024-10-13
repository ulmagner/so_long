/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 22:58:41 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
			ft_pixel_put(&all->plan, x,
				y, color);
		}
	}
}

void	copy_game_to_map(t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;
	int				x_offset;
	int				y_offset;

	x_offset = (all->plan.w - all->game.w) / 2;
	y_offset = (all->plan.h - all->game.h) / 2;
	y = -1;
	while (++y < all->game.h)
	{
		x = -1;
		while (++x < all->game.w)
		{
			if (x_offset + x >= 0 && x_offset + x < all->plan.w \
				&& y_offset + y >= 0 && y_offset + y < all->plan.h)
			{
				color = get_pixel_color(&all->plan, x_offset + x, y_offset + y);
				ft_pixel_put(&all->game, x, y, color);
			}
		}
	}
}
