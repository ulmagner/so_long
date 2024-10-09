/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 20:00:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_map(t_all *all, t_window *window)
{
	int	i;

	i = -1;
	build_game(all);
	while (++i < all->info.ennemies)
		copy_oeuil_to_map(all, &all->oeuil[i]);
	i = -1;
	slime_handling(all, all->slime);
	copy_player_to_map(all);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i]);
	mlx_put_image_to_window(window->mlx,
		window->main, all->game.img, 0, 0);
	return (1);
}

static int	looping(t_all *all)
{
	int	i;

	i = -1;
	all->i++;
	if (all->i % 1500 != 0)
		return (0);
	copy_ground_to_map(all);
	get_hitbox_player(&all->player);
	while (++i < all->info.ennemies && !all->player.is_dead)
	{
		if (!all->oeuil[i].is_dead && !all->oeuil[i].is_stun)
		{
			get_hitbox_oeuil(&all->oeuil[i]);
			movement_handling_oeuil(all, &all->oeuil[i]);
		}
	}
	if (!all->player.is_dead)
	{
		movement_handling(all);
		action_handling(all);
	}
	if (!display_map(all, &all->window))
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	init_bg(t_image *ground, t_image *game, t_info *info, t_window *window)
{
	int	map_width_in_pixels;
	int	map_height_in_pixels;

	map_width_in_pixels = info->column * TILE_SIZE;
	map_height_in_pixels = info->line * TILE_SIZE;
	ground->width = map_width_in_pixels;
	ground->height = map_height_in_pixels;
	game->width = map_width_in_pixels;
	game->height = map_height_in_pixels;
	ground->img = mlx_new_image(window->mlx,
			map_width_in_pixels, map_height_in_pixels);
	ground->addr = mlx_get_data_addr(ground->img,
			&ground->bits_per_pixel,
			&ground->line_length, &ground->endian);
	game->img = mlx_new_image(window->mlx,
			map_width_in_pixels, map_height_in_pixels);
	game->addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel,
			&game->line_length, &game->endian);
	return (1);
}

int	init_window(t_all *all, char **av)
{
	all->window.main_width = ft_atoi(av[2]);
	all->window.main_height = ft_atoi(av[3]);
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_width, all->window.main_height, "So_long");
}

int	launcher(t_all *all, char **av)
{
	init_window(all, av);
	if (!split_tileset(all, &all->info))
		return (0);
	init_bg(&all->ground, &all->game, &all->info, &all->window);
	all->deco.i = 2;
	all->random.rd_floor = get_randoms(0, 1, 2);
	all->info.collectible = all->info.coin;
	all->player.animation = ft_calloc(9, sizeof(int));
	if (!all->player.animation)
		return (0);
	all->slime = ft_calloc(all->info.collectible, sizeof(t_slime));
	if (!all->slime)
		return (0);
	all->trap = ft_calloc(all->info.trap, sizeof(t_trap));
	if (!all->trap)
		return (0);
	build_map(all);
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
