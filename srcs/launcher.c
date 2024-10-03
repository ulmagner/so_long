/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/03 10:04:19 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_map(t_solong *solong, t_window *window)
{
	build_map(solong);
	copy_player_to_map(solong);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->ground.img, 0, 0);
	return (1);
}

static int	looping(t_solong *solong)
{
	movement_handling(solong);
	attack_handling(solong, &solong->player);
	if (!display_map(solong, &solong->window))
		exit((ft_clearall(solong), EXIT_FAILURE));
	solong->i++;
	return (0);
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
	solong->ground.img = mlx_new_image(solong->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	solong->ground.addr = mlx_get_data_addr(solong->ground.img,
			&solong->ground.bits_per_pixel,
			&solong->ground.line_length, &solong->ground.endian);
	solong->player.animation = malloc(sizeof(int) * 6);
	if (!solong->player.animation)
		return (0);
	ft_bzero(solong->player.animation, sizeof(int) * 6);
	mlx_hook(solong->window.main, 2, 1L << 0, movement_p, solong);
	mlx_hook(solong->window.main, 3, 1L << 1, movement_r, solong);
	mlx_hook(solong->window.main, 4, 1L << 2, attack_p, solong);
	mlx_hook(solong->window.main, 5, 1L << 3, attack_r, solong);
	mlx_loop_hook(solong->window.mlx, looping, solong);
	mlx_loop(solong->window.mlx);
	return (1);
}
