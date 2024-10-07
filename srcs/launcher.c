/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/07 15:38:58 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_map(t_solong *solong, t_window *window)
{
	int	i;

	i = -1;
	
	build_game(solong);
	while (solong->slime[++i].is_free && i < solong->info.collectible)
	{
		solong->slime[i].anim_slime = (solong->slime[i].anim_slime + 1) % 5;
		if (solong->movement.index_move[0] && solong->slime[i].y > solong->player.y + 32)
		{
			if (solong->slime[i].y > solong->player.y + 32 + (i * 32))
				solong->slime[i].y--;
			if (solong->slime[i].x < solong->player.x)
				solong->slime[i].x++;
			else if (solong->slime[i].x > solong->player.x)
				solong->slime[i].x--;
		}
		else if (solong->movement.index_move[1] && solong->slime[i].y <= solong->player.y - 32)
		{
			if (solong->slime[i].x < solong->player.x)
				solong->slime[i].x++;
			else if (solong->slime[i].x > solong->player.x)
				solong->slime[i].x--;
			if (solong->slime[i].y <= solong->player.y - 32 - (i * 32))
				solong->slime[i].y++;
		}
		else if (solong->movement.index_move[2] && solong->slime[i].x > solong->player.x + 32)
		{
			if (solong->slime[i].x > solong->player.x + 32 + (i * 32))
				solong->slime[i].x--;
			if (solong->slime[i].y < solong->player.y + 10)
				solong->slime[i].y++;
			else if (solong->slime[i].y > solong->player.y + 10)
				solong->slime[i].y--;
		}
		else if (solong->movement.index_move[3] && solong->slime[i].x <= solong->player.x - 32)
		{
			if (solong->slime[i].x <= solong->player.x - 32 - (i * 32))
				solong->slime[i].x++;
			if (solong->slime[i].y < solong->player.y - 10)
				solong->slime[i].y++;
			else if (solong->slime[i].y > solong->player.y - 10)
				solong->slime[i].y--;
		}
		copy_slime_to_map(solong, &solong->slime[i]);
	}
	copy_oeuil_to_map(solong);
	copy_player_to_map(solong);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->game.img, 0, 0);
	return (1);
}

static int	looping(t_solong *solong)
{
	copy_ground_to_map(solong);
	movement_handling(solong);
	movement_handling_oeuil(solong);
	action_handling(solong);
	if (solong->player.hero->is_visited == 2 && solong->player.hero->index == 'C')
	{
		solong->slime[solong->info.slime].y = solong->player.y;
		solong->slime[solong->info.slime].x = solong->player.x;
		if (!solong->slime[solong->info.slime].is_free)
			copy_tile_to_map(&solong->tileset[2][2][0], &solong->game, solong->player.hero);
		else
			solong->info.slime++;
		if (solong->movement.move[XK_e])
		{
			solong->player.hero->index = '0';
			solong->info.coin--;
			solong->slime[solong->info.slime].is_free = 1;
		}
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
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
	solong->player.animation = malloc(sizeof(int) * 6);
	if (!solong->player.animation)
		return (0);
	ft_bzero(solong->player.animation, sizeof(int) * 6);
	solong->oeuil.animation = malloc(sizeof(int) * 6);
	if (!solong->oeuil.animation)
		return (0);
	ft_bzero(solong->oeuil.animation, sizeof(int) * 6);
	solong->random.rd_floor = get_randoms(0, 1, 2);
	solong->deco.index = 2;
	solong->info.collectible = solong->info.coin;
	solong->slime = malloc(sizeof(t_slime) * solong->info.collectible);
	if (!solong->slime)
		return (0);
	ft_bzero(solong->slime, sizeof(t_slime) * solong->info.collectible);
	build_map(solong);
	mlx_hook(solong->window.main, 2, 1L << 0, movement_p, solong);
	mlx_hook(solong->window.main, 3, 1L << 1, movement_r, solong);
	mlx_hook(solong->window.main, 4, 1L << 2, action_p, solong);
	mlx_hook(solong->window.main, 5, 1L << 3, action_r, solong);
	mlx_loop_hook(solong->window.mlx, looping, solong);
	mlx_loop(solong->window.mlx);
	return (1);
}
