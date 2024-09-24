/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/24 13:03:42 by ulmagner         ###   ########.fr       */
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
unsigned int get_pixel_color(t_image *image, int x, int y)
{
    char    *src;

    src = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
    return *(unsigned int *)src;
}

void	copy_tile_to_map(t_solong *solong, int tile_x, int tile_y, int map_x, int map_y)
{
    int x, y;
    unsigned int color;

    for (y = 0; y < TILE_SIZE; y++) {
        for (x = 0; x < TILE_SIZE; x++) {
            color = get_pixel_color(&solong->tileset, tile_x * TILE_SIZE + x, tile_y * TILE_SIZE + y);
            ft_pixel_put(&solong->tileset, map_x * TILE_SIZE + x, map_y * TILE_SIZE + y, color);
        }
    }
}

void build_map(t_solong *solong, int map[MAP_HEIGHT][MAP_WIDTH])
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 0) {
                // Copier la tuile "sol" (par exemple, 0,0 dans le tileset)
                copy_tile_to_map(solong, 0, 0, x, y);
            } else if (map[y][x] == 1) {
                // Copier une autre tuile (par exemple, 1,0 dans le tileset)
                copy_tile_to_map(solong, 1, 0, x, y);
            }
            // Ajoute des conditions pour d'autres types de tuiles si nécessaire
        }
    }
}

int	launcher(t_solong *solong, char **av)
{
	solong->tileset.img_path = "./RF_Catacombs_v1.0/tilesfloor.xpm";
	solong->window.mlx = mlx_init();
	solong->window.main = mlx_new_window(solong->window.mlx, \
		ft_atoi(av[2]), ft_atoi(av[3]), "So_long");
	mlx_hook(solong->window.main, 2, 1L << 0, close_mlx, solong);
	solong->tileset.img = mlx_xpm_file_to_image(solong->window.mlx, solong->tileset.img_path, &solong->tileset.width, &solong->tileset.height);
	solong->tileset.addr = mlx_get_data_addr(solong->tileset.img, &solong->tileset.bits_per_pixel, &solong->tileset.line_length, &solong->tileset.endian);
	
	mlx_put_image_to_window(solong->window.mlx, solong->window.main, solong->tileset.img, 500, 500);
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
