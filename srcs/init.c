/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:42:35 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 22:49:13 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	init_game(t_image *game, t_window *window)
{
	game->w = window->main_w;
	game->h = window->main_h;
	game->img = mlx_new_image(window->mlx,
			game->w, game->h);
	game->addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel,
			&game->line_length, &game->endian);
	return (1);
}

int	init_bg(t_image *ground, t_image *plan, t_all *all, t_window *window)
{
	int	map_w_in_pixels;
	int	map_h_in_pixels;

	map_w_in_pixels = all->info.column * TILE_SIZE;
	map_h_in_pixels = all->info.line * TILE_SIZE;
	printf("%d %d\n", map_h_in_pixels, map_w_in_pixels);
	ground->w = map_w_in_pixels;
	ground->h = map_h_in_pixels;
	plan->w = map_w_in_pixels;
	plan->h = map_h_in_pixels;
	ground->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	ground->addr = mlx_get_data_addr(ground->img,
			&ground->bits_per_pixel,
			&ground->line_length, &ground->endian);
	plan->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	plan->addr = mlx_get_data_addr(plan->img,
			&plan->bits_per_pixel,
			&plan->line_length, &plan->endian);
	all->argb = (t_color){0, 0, 0, 0};
	return (1);
}

int	init_window(t_all *all, char **av)
{
	all->window.main_w = ft_atoi(av[2]);
	all->window.main_h = ft_atoi(av[3]) - 70;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_w, all->window.main_h, "So_long");
	return (1);
}
