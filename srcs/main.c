/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 23:00:29 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	close_mlx(int keycode, t_solong *solong)
{
	if (keycode == XK_Escape)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (0);
}

int	display_map(t_solong *solong, t_window *window)
{
	int	map_width_in_pixels;
	int	map_height_in_pixels;

	solong->tileset = split_tileset(solong);
	if (!solong->tileset)
		return (0);
	map_width_in_pixels = solong->info.nbr_column * TILE_SIZE;
	map_height_in_pixels = solong->info.nbr_line * TILE_SIZE;
	solong->ground.img = mlx_new_image(window->mlx,
			map_width_in_pixels, map_height_in_pixels);
	solong->ground.addr = mlx_get_data_addr(solong->ground.img,
			&solong->ground.bits_per_pixel,
			&solong->ground.line_length, &solong->ground.endian);
	build_map(solong);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->ground.img, 0, 0);
	return (1);
}

int	launcher(t_solong *solong, char **av)
{
	solong->window.main_width = ft_atoi(av[2]);
	solong->window.main_height = ft_atoi(av[3]);
	solong->window.mlx = mlx_init();
	solong->window.main = mlx_new_window(solong->window.mlx, \
		solong->window.main_width, solong->window.main_height, "So_long");
	if (!display_map(solong, &solong->window))
		exit((ft_clearall(solong), EXIT_FAILURE));
	mlx_hook(solong->window.main, 2, 1L << 0, close_mlx, solong);
	mlx_loop(solong->window.mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_solong	solong;

	solong = (t_solong){0};
	if (!error_handling(ac, av, &solong.info))
		return (EXIT_FAILURE);
	if (!get_paths(av[4], &solong.info))
		return (EXIT_FAILURE);
	if (!map_handling(&solong.info, &solong.map, &solong.player))
		return (ft_clearall(&solong), EXIT_FAILURE);
	if (!launcher(&solong, av))
		return (ft_clearall(&solong), EXIT_FAILURE);
	return (ft_clearall(&solong), EXIT_SUCCESS);
}
