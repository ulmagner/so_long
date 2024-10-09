/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
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

int	launcher(t_all *all, char **av)
{
	int	map_width_in_pixels;
	int	map_height_in_pixels;

	all->window.main_width = ft_atoi(av[2]);
	all->window.main_height = ft_atoi(av[3]);
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_width, all->window.main_height, "So_long");
	if (!split_tileset(all, &all->info))
		return (0);
	map_width_in_pixels = all->info.column * TILE_SIZE;
	map_height_in_pixels = all->info.line * TILE_SIZE;
	all->ground.width = map_width_in_pixels;
	all->ground.height = map_height_in_pixels;
	all->game.width = map_width_in_pixels;
	all->game.height = map_height_in_pixels;
	all->ground.img = mlx_new_image(all->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	all->ground.addr = mlx_get_data_addr(all->ground.img,
			&all->ground.bits_per_pixel,
			&all->ground.line_length, &all->ground.endian);
	all->game.img = mlx_new_image(all->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	all->game.addr = mlx_get_data_addr(all->game.img,
			&all->game.bits_per_pixel,
			&all->game.line_length, &all->game.endian);
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
