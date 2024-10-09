/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:05:12 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_map(t_solong *solong, t_window *window)
{
	int	i;

	i = -1;
	build_game(solong);
	while (++i < solong->info.ennemies)
		copy_oeuil_to_map(solong, &solong->oeuil[i]);
	i = -1;
	slime_handling(solong, solong->slime);
	copy_player_to_map(solong);
	i = -1;
	while (++i < solong->info.trap)
		trap_handling(solong, &solong->trap[i]);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->game.img, 0, 0);
	return (1);
}

static int	looping(t_solong *solong)
{
	int	i;

	i = -1;
	solong->i++;
	if (solong->i % 1500 != 0)
		return (0);
	copy_ground_to_map(solong);
	get_hitbox_player(&solong->player);
	while (++i < solong->info.ennemies && !solong->player.is_dead)
	{
		if (!solong->oeuil[i].is_dead && !solong->oeuil[i].is_stun)
		{
			get_hitbox_oeuil(&solong->oeuil[i]);
			movement_handling_oeuil(solong, &solong->oeuil[i]);
		}
	}
	if (!solong->player.is_dead)
	{
		movement_handling(solong);
		action_handling(solong);
	}
	if (!display_map(solong, &solong->window))
		exit((ft_clearall(solong), EXIT_FAILURE));
	return (1);
}

int	launcher(t_solong *solong, char **av)
{
	int	map_width_in_pixels;
	int	map_height_in_pixels;

	solong->window.main_width = ft_atoi(av[2]);
	solong->window.main_height = ft_atoi(av[3]);
	solong->window.mlx = mlx_init();
	if (!solong->window.mlx)
		return (0);
	solong->window.main = mlx_new_window(solong->window.mlx, \
		solong->window.main_width, solong->window.main_height, "So_long");
	if (!split_tileset(solong, &solong->info))
		return (0);
	map_width_in_pixels = solong->info.nbr_column * TILE_SIZE;
	map_height_in_pixels = solong->info.nbr_line * TILE_SIZE;
	solong->ground.width = map_width_in_pixels;
	solong->ground.height = map_height_in_pixels;
	solong->game.width = map_width_in_pixels;
	solong->game.height = map_height_in_pixels;
	solong->ground.img = mlx_new_image(solong->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	solong->ground.addr = mlx_get_data_addr(solong->ground.img,
			&solong->ground.bits_per_pixel,
			&solong->ground.line_length, &solong->ground.endian);
	solong->game.img = mlx_new_image(solong->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	solong->game.addr = mlx_get_data_addr(solong->game.img,
			&solong->game.bits_per_pixel,
			&solong->game.line_length, &solong->game.endian);
	solong->deco.index = 2;
	solong->random.rd_floor = get_randoms(0, 1, 2);
	solong->info.collectible = solong->info.coin;
	solong->player.animation = ft_calloc(9, sizeof(int));
	if (!solong->player.animation)
		return (0);
	solong->slime = ft_calloc(solong->info.collectible, sizeof(t_slime));
	if (!solong->slime)
		return (0);
	solong->trap = ft_calloc(solong->info.trap, sizeof(t_trap));
	if (!solong->trap)
		return (0);
	build_map(solong);
	mlx_hook(solong->window.main, 2, 1L << 0, movement_p, solong);
	mlx_hook(solong->window.main, 3, 1L << 1, movement_r, solong);
	mlx_hook(solong->window.main, 4, 1L << 2, action_p, solong);
	mlx_hook(solong->window.main, 5, 1L << 3, action_r, solong);
	mlx_loop_hook(solong->window.mlx, looping, solong);
	mlx_loop(solong->window.mlx);
	return (1);
}
