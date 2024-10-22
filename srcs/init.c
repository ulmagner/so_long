/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:42:35 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/22 19:26:56 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	init_game(t_image *game, t_window *window, t_all *all)
{
	game->w = all->window.main_w;
	game->h = all->window.main_h;
	game->img = mlx_new_image(window->mlx, game->w, game->h);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	return (1);
}

int	init_bg(t_image *ground, t_image *plan, t_all *all, t_window *window)
{
	int	map_w_in_pixels;
	int	map_h_in_pixels;

	map_w_in_pixels = all->info.column * TILE_SIZE;
	map_h_in_pixels = all->info.line * TILE_SIZE;
	ground->w = map_w_in_pixels;
	ground->h = map_h_in_pixels;
	plan->w = map_w_in_pixels;
	plan->h = map_h_in_pixels;
	ground->img = mlx_new_image(window->mlx, map_w_in_pixels, map_h_in_pixels);
	if (!ground->img)
		return (0);
	ground->addr = mlx_get_data_addr(ground->img, &ground->bits_per_pixel,
			&ground->line_length, &ground->endian);
	if (!ground->addr)
		return (0);
	plan->img = mlx_new_image(window->mlx, map_w_in_pixels, map_h_in_pixels);
	if (!plan->img)
		return (0);
	plan->addr = mlx_get_data_addr(plan->img, &plan->bits_per_pixel,
			&plan->line_length, &plan->endian);
	if (!plan->addr)
		return (0);
	all->argb = (t_color){0, 0, 0, 0};
	return (1);
}

int	init_window(t_all *all)
{
	all->window.main_w = 1920;
	all->window.main_h = 1010;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_w, all->window.main_h, "So_long");
	if (!all->window.main)
		return (0);
	return (1);
}

int	init_char(t_all *all, t_info *info)
{
	int	i;

	i = -1;
	all->info.ennemies = 10;
	all->oeil = ft_calloc(info->oeil, sizeof(t_oeil *));
	while (++i < info->oeil)
	{
		all->oeil[i] = ft_calloc(info->ennemies, sizeof(t_oeil));
		if (!all->oeil[i])
			return (0);
	}
	all->slime = ft_calloc(info->coin, sizeof(t_slime));
	if (!all->slime)
		return (0);
	all->trap = ft_calloc(info->trap, sizeof(t_trap));
	if (!all->trap)
		return (0);
	return (1);
}

void	init_variables(t_all *all)
{
	all->player.ms = 4;
	all->step = 0;
	all->i = -1;
	all->frame = 0;
	all->frameplayer = 0;
	all->vision = 300.0f;
	all->counter.curr_frame_c = 0;
	all->counter.tot_frame_c = 100;
	all->attack.curr_frame_c = 0;
	all->attack.tot_frame_c = 100;
}
