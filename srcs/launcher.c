/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 16:33:47 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_map(t_all *all, t_window *window)
{
	int	i;

	i = -1;
	build_game(all);
	while (++i < all->info.ennemies)
	{
		if (all->dist.p_o[i] <= 300.0f)
			copy_oeuil_to_map(all, &all->oeuil[i]);
	}
	i = -1;
	slime_handling(all, all->slime);
	copy_player_to_map(all);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i], i);
	copy_fog_map(all);
	if (all->player.is_dead)
		copy_game_map(&all->tileset[8][0][0], &all->game, all);
	mlx_put_image_to_window(window->mlx,
		window->main, all->game.img, \
		((all->window.main_w / 2) - ((all->info.column * 64) / 2)), \
		((all->window.main_h / 2) - ((all->info.line * 64) / 2)));
	return (1);
}

static int	looping(t_all *all)
{
	int	i;

	i = -1;
	if (++(all->i) % 1500 != 0)
		return (0);
	calcul_dist(all);
	copy_ground_to_map(all);
	get_hitbox_player(&all->player);
	while (++i < all->info.ennemies)
	{
		if (!all->oeuil[i].is_dead && !all->oeuil[i].is_stun \
			&& !all->player.is_dead)
		{
			get_hitbox_oeuil(&all->oeuil[i]);
			movement_handling_oeuil(all, &all->oeuil[i], i);
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

int	init_bg(t_image *ground, t_image *game, t_all *all, t_window *window)
{
	int	map_w_in_pixels;
	int	map_h_in_pixels;

	map_w_in_pixels = all->info.column * TILE_SIZE;
	map_h_in_pixels = all->info.line * TILE_SIZE;
	ground->w = map_w_in_pixels;
	ground->h = map_h_in_pixels;
	game->w = map_w_in_pixels;
	game->h = map_h_in_pixels;
	ground->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	ground->addr = mlx_get_data_addr(ground->img,
			&ground->bits_per_pixel,
			&ground->line_length, &ground->endian);
	game->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	game->addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel,
			&game->line_length, &game->endian);
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

int	launcher(t_all *all, char **av)
{
	init_window(all, av);
	if (!split_tileset(all, &all->info))
		return (0);
	init_bg(&all->ground, &all->game, all, &all->window);
	all->deco.i = 2;
	all->random.rd_floor = get_randoms(0, 1, 2);
	all->info.collectible = all->info.coin;
	all->player.animation = ft_calloc(9, sizeof(int));
	if (!all->player.animation)
		return (0);
	build_map(all);
	init_distances(all);
	all->player.ms = 4;
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
