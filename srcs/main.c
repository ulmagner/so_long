/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 13:22:15 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	display_map(t_solong *solong, t_window *window)
{
	int	map_width_in_pixels;
	int	map_height_in_pixels;

	map_width_in_pixels = solong->info.nbr_column * TILE_SIZE;
	map_height_in_pixels = solong->info.nbr_line * TILE_SIZE;
	solong->ground.img = mlx_new_image(solong->window.mlx,
			map_width_in_pixels, map_height_in_pixels);
	solong->ground.addr = mlx_get_data_addr(solong->ground.img,
			&solong->ground.bits_per_pixel,
			&solong->ground.line_length, &solong->ground.endian);
	build_map(solong);
	copy_player_to_map(solong);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->ground.img, 0, 0);
	return (1);
}

int	movement_p(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (0);
}

int	movement_r(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = false;
	return (0);
}

int	movement_handling(t_solong *solong)
{
	if (solong->i % 2 != 0)
		return (0);
	if (solong->movement.move[XK_w])
	{
		solong->player.hero = solong->player.hero->up;
	}
	if (solong->movement.move[XK_s])
	{
		solong->player.hero = solong->player.hero->down;
	}
	if (solong->movement.move[XK_a])
	{
		solong->player.hero = solong->player.hero->left;
	}
	if (solong->movement.move[XK_d])
	{
		solong->player.hero = solong->player.hero->right;
	}
	return (1);
}

int	looping(t_solong *solong)
{
	movement_handling(solong);
	if (!display_map(solong, &solong->window))
		exit((ft_clearall(solong), EXIT_FAILURE));
	solong->i++;
	return (0);
}

int	launcher(t_solong *solong, char **av)
{
	solong->window.main_width = ft_atoi(av[2]);
	solong->window.main_height = ft_atoi(av[3]);
	solong->window.mlx = mlx_init();
	solong->window.main = mlx_new_window(solong->window.mlx, \
		solong->window.main_width, solong->window.main_height, "So_long");
	solong->tileset = split_tileset(solong);
	if (!solong->tileset)
		return (0);
	mlx_hook(solong->window.main, 2, 1L << 0, movement_p, solong);
	mlx_hook(solong->window.main, 3, 1L << 1, movement_r, solong);
	mlx_loop_hook(solong->window.mlx, looping, solong);
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
