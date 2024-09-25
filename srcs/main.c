/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 10:24:50 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	close_mlx(int keycode, t_solong *solong)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_image(solong->window.mlx, solong->tileset.img);
		mlx_destroy_window(solong->window.mlx, solong->window.main);
		mlx_destroy_display(solong->window.mlx);
		exit((ft_clearall(solong), EXIT_SUCCESS));
	}
	return (0);
}

void	ft_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	char	*src;

	src = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

void	copy_tile_to_map(t_solong *solong, int tile_x, int tile_y, int map_x, int map_y)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			color = get_pixel_color(&solong->tileset, tile_x * TILE_SIZE + x, tile_y * TILE_SIZE + y);
			ft_pixel_put(&solong->ground, map_x * TILE_SIZE + x, map_y * TILE_SIZE + y, color);
		}
	}
}

void	build_map(t_solong *solong)
{
	t_map	*col;

	col = solong->map;
	while (col)
	{
		copy_tile_to_map(solong, 0, 0, col->x, col->y);
		col = col->right;
	}
}

int	launcher(t_solong *solong, char **av)
{
	solong->window.main_width = ft_atoi(av[2]);
	solong->window.main_height = ft_atoi(av[3]);
	solong->window.mlx = mlx_init();
	solong->window.main = mlx_new_window(solong->window.mlx, \
		solong->window.main_width, solong->window.main_height, "So_long");
	solong->tileset.img_path = "./RF_Catacombs_v1.0/tilesfloor.xpm";
	solong->tileset.img = mlx_xpm_file_to_image(solong->window.mlx, solong->tileset.img_path, &solong->tileset.width, &solong->tileset.height);
	solong->tileset.addr = mlx_get_data_addr(solong->tileset.img, &solong->tileset.bits_per_pixel, &solong->tileset.line_length, &solong->tileset.endian);
	int	map_width_in_pixels = solong->info.nbr_column * TILE_SIZE;
	int	map_height_in_pixels = solong->info.nbr_line * TILE_SIZE;
	solong->ground.img = mlx_new_image(solong->window.mlx, map_width_in_pixels, map_height_in_pixels);
	solong->ground.addr = mlx_get_data_addr(solong->ground.img, &solong->ground.bits_per_pixel, &solong->ground.line_length, &solong->ground.endian);
	build_map(solong);
	mlx_put_image_to_window(solong->window.mlx, solong->window.main, solong->ground.img, 0, 0);
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
	if (!map_handling(&solong.info, &solong.map, &solong.player))
		return (ft_clearall(&solong), EXIT_FAILURE);
	if (!launcher(&solong, av))
		return (ft_clearall(&solong), EXIT_FAILURE);
	return (ft_clearall(&solong), EXIT_SUCCESS);
}
