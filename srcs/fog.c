/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:06:36 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 16:57:50 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

float	calculate_distance(t_player *player, float obj_x, float obj_y, int off)
{
	return (sqrt(pow(player->x + off - obj_x, 2) \
		+ pow(player->y + off - obj_y, 2)));
}

static int	lerp_color(int color, t_color fog_color, float fog_factor)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (1.0f - fog_factor) * a + fog_factor * fog_color.a;
	r = (1.0f - fog_factor) * r + fog_factor * fog_color.r;
	g = (1.0f - fog_factor) * g + fog_factor * fog_color.g;
	b = (1.0f - fog_factor) * b + fog_factor * fog_color.b;
	if (a > 255)
		a = 255;
	if (a < 0)
		a = 0;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

static int	apply_fog(int color, t_all *all, t_color fog_color)
{
	float	fog_factor;

	fog_factor = 0.0;
	if (all->dist.p_f >= 100.0)
	{
		color = (color >> 1) & 8355711;
		if (all->dist.p_f >= 300.0)
			fog_factor = 0.7;
		else
			fog_factor = (all->dist.p_f - 100.0) / (300.0 - 100.0) - 0.3;
		return (lerp_color(color, fog_color, fog_factor));
	}
	return (color);
}

void	copy_fog_map(t_all *all)
{
	int	x;
	int	y;
	int	original_color;
	int	fogged_color;

	y = -1;
	while (++y < all->game.h)
	{
		x = -1;
		while (++x < all->game.w)
		{
			original_color = get_pixel_color(&all->game, x, y);
			all->dist.p_f = calculate_distance(&all->player, x, y, 32);
			fogged_color = apply_fog(original_color, all, all->argb);
			ft_pixel_put(&all->game, x, y, fogged_color);
		}
	}
}
