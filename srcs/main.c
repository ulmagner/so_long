/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 20:06:37 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	close_mlx(int keycode, t_solong *solong)
{
	if (keycode == XK_Escape)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (0);
}

void	floor_image(t_image *floor, t_window *window)
{
	floor[0].img_path = "./RF_Catacombs_v1.0/tilesfloor.xpm";
	floor[0].img = mlx_xpm_file_to_image(window->mlx, \
		floor[0].img_path, &floor[0].width, &floor[0].height);
	floor[0].addr = mlx_get_data_addr(floor[0].img, \
		&floor[0].bits_per_pixel, &floor[0].line_length, &floor[0].endian);
}

void	exit_image(t_image *exite, t_window *window)
{
	exite[0].img_path = "./RF_Catacombs_v1.0/exit1.xpm";
	exite[0].img = mlx_xpm_file_to_image(window->mlx, \
		exite[0].img_path, &exite[0].width, &exite[0].height);
	exite[0].addr = mlx_get_data_addr(exite[0].img, \
		&exite[0].bits_per_pixel, &exite[0].line_length, &exite[0].endian);
}

void	wall_image(t_image *wall, t_window *window)
{
	wall[0].img_path = "./RF_Catacombs_v1.0/wall_sud1.xpm";
	wall[0].img = mlx_xpm_file_to_image(window->mlx, \
		wall[0].img_path, &wall[0].width, &wall[0].height);
	wall[0].addr = mlx_get_data_addr(wall[0].img, \
		&wall[0].bits_per_pixel, &wall[0].line_length, &wall[0].endian);
	wall[1].img_path = "./RF_Catacombs_v1.0/wall_ouest1.xpm";
	wall[1].img = mlx_xpm_file_to_image(window->mlx, \
		wall[1].img_path, &wall[1].width, &wall[1].height);
	wall[1].addr = mlx_get_data_addr(wall[1].img, \
		&wall[1].bits_per_pixel, &wall[1].line_length, &wall[1].endian);
	wall[2].img_path = "./RF_Catacombs_v1.0/wall_nord1.xpm";
	wall[2].img = mlx_xpm_file_to_image(window->mlx, \
		wall[2].img_path, &wall[2].width, &wall[2].height);
	wall[2].addr = mlx_get_data_addr(wall[2].img, \
		&wall[2].bits_per_pixel, &wall[2].line_length, &wall[2].endian);
	wall[3].img_path = "./RF_Catacombs_v1.0/wall_est1.xpm";
	wall[3].img = mlx_xpm_file_to_image(window->mlx, \
		wall[3].img_path, &wall[3].width, &wall[3].height);
	wall[3].addr = mlx_get_data_addr(wall[3].img, \
		&wall[3].bits_per_pixel, &wall[3].line_length, &wall[3].endian);
}

void	deco_image(t_image *deco, t_window *window)
{
	deco[0].img_path = "./RF_Catacombs_v1.0/deco1.xpm";
	deco[0].img = mlx_xpm_file_to_image(window->mlx, \
		deco[0].img_path, &deco[0].width, &deco[0].height);
	deco[0].addr = mlx_get_data_addr(deco[0].img, \
		&deco[0].bits_per_pixel, &deco[0].line_length, &deco[0].endian);
}

void	coin_image(t_image *coin, t_window *window)
{
	coin[0].img_path = "./one/user interface/highlight/coin1.xpm";
	coin[0].img = mlx_xpm_file_to_image(window->mlx, \
		coin[0].img_path, &coin[0].width, &coin[0].height);
	coin[0].addr = mlx_get_data_addr(coin[0].img, \
		&coin[0].bits_per_pixel, &coin[0].line_length, &coin[0].endian);
}

void	player_image(t_image *player, t_window *window)
{
	player[0].img_path = "./one/playable character/warrior/warrior/E/player_est1.xpm";
	player[0].img = mlx_xpm_file_to_image(window->mlx, \
		player[0].img_path, &player[0].width, &player[0].height);
	player[0].addr = mlx_get_data_addr(player[0].img, \
		&player[0].bits_per_pixel, &player[0].line_length, &player[0].endian);
}

int	display_map(t_solong *solong, t_window *window)
{
	// int	map_width_in_pixels;
	// int	map_height_in_pixels;
	(void) window;

	solong->tileset = split_tileset(solong);
	if (!solong->tileset)
		return (0);
	// map_width_in_pixels = solong->info.nbr_column * TILE_SIZE;
	// map_height_in_pixels = solong->info.nbr_line * TILE_SIZE;
	// solong->ground.img = mlx_new_image(window->mlx, \
	// 	map_width_in_pixels, map_height_in_pixels);
	// solong->ground.addr = mlx_get_data_addr(solong->ground.img, \
	// 	&solong->ground.bits_per_pixel, \
	// 	&solong->ground.line_length, &solong->ground.endian);
	// build_map(solong);
	// mlx_put_image_to_window(window->mlx, \
	// 	window->main, solong->ground.img, 0, 0);
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
		return (/*ft_clearall(&solong), */EXIT_FAILURE);
	return (/*ft_clearall(&solong), */EXIT_SUCCESS);
}
