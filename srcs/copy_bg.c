/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:50:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 10:09:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_ground_plan(t_all *all)
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

void	copy_plan_to_game(t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	while (++y < all->plan.h)
	{
		x = -1;
		while (++x < all->plan.w)
		{
			color = get_pixel_color(&all->plan, x, y);
			ft_pixel_put(&all->game, x, y, color);
		}
	}
}
