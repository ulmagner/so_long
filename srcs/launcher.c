/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/08 18:19:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	move_slime(t_player player, t_slime *slime, int off_x, int off_y)
{
	if (slime->y > player.y + off_y)
		slime->y -= player.ms;
	else if (slime->y < player.y + off_y)
		slime->y += player.ms;
	if (slime->x > player.x + off_x)
		slime->x -= player.ms;
	else if (slime->x < player.x + off_x)
		slime->x += player.ms;
	return (1);
}

static int	display_map(t_solong *solong, t_window *window)
{
	int	i;

	i = -1;

	build_game(solong);
	copy_oeuil_to_map(solong);
	while (solong->slime[++i].is_free && i < solong->info.collectible)
	{
		copy_slime_to_map(solong, &solong->slime[i]);
		if (solong->i % 10000 == 0)
			solong->slime[i].anim_slime = (solong->slime[i].anim_slime + 1) % 5;
		if (solong->movement.index_move[0])
			move_slime(solong->player, &solong->slime[i], 0, (32 + (i * 32)));
		else if (solong->movement.index_move[1])
			move_slime(solong->player, &solong->slime[i], 0, (-32 - (i * 32)));
		if (solong->movement.index_move[2])
			move_slime(solong->player, &solong->slime[i], (32 + (i * 32)), 0);
		else if (solong->movement.index_move[3])
			move_slime(solong->player, &solong->slime[i], (-32 - (i * 32)), 0);
	}
	copy_player_to_map(solong);
	mlx_put_image_to_window(window->mlx,
		window->main, solong->game.img, 0, 0);
	return (1);
}

int	get_interaction_player(t_player *player)
{
	player->interaction[0][0] = player->hero->x_pxl + 32;
	player->interaction[0][1] = player->hero->y_pxl;
	player->interaction[1][0] = player->hero->x_pxl + 32;
	player->interaction[1][1] = player->hero->y_pxl + 64;
	player->interaction[2][0] = player->hero->x_pxl;
	player->interaction[2][1] = player->hero->y_pxl + 32;
	player->interaction[3][0] = player->hero->x_pxl + 64;
	player->interaction[3][1] = player->hero->y_pxl + 32;
	return (1);
}

int	get_interaction_oeuil(t_oeuil *oeuil)
{
	oeuil->interaction[0][0] = oeuil->o->x_pxl + 32;
	oeuil->interaction[0][1] = oeuil->o->y_pxl + 16;
	oeuil->interaction[1][0] = oeuil->o->x_pxl + 32;
	oeuil->interaction[1][1] = oeuil->o->y_pxl + 48;
	oeuil->interaction[2][0] = oeuil->o->x_pxl + 16;
	oeuil->interaction[2][1] = oeuil->o->y_pxl + 32;
	oeuil->interaction[3][0] = oeuil->o->x_pxl + 48;
	oeuil->interaction[3][1] = oeuil->o->y_pxl + 32;
	return (1);
}

static int	looping(t_solong *solong)
{
	solong->i++;
	if (solong->i % 5000 != 0)
		return (0);
	copy_ground_to_map(solong);
	get_interaction_player(&solong->player);
	get_interaction_oeuil(&solong->oeuil);
	if (!solong->player.is_dead)
	{
		movement_handling(solong);
		action_handling(solong);
	}
	if (!solong->oeuil.is_dead && !solong->oeuil.is_stun && !solong->player.is_dead)
	{
		movement_handling_oeuil(solong);
	}
	if (solong->player.hero->is_visited == 2 && solong->player.hero->index == 'C')
	{
		if (!solong->slime[solong->info.slime].is_free)
			copy_tile_to_map(&solong->tileset[2][2][0], &solong->game, solong->player.hero);
		else
			solong->info.slime++;
		if (solong->movement.move[XK_e])
		{
			solong->slime[solong->info.slime].y = solong->player.y;
			solong->slime[solong->info.slime].x = solong->player.x;
			solong->player.hero->index = '0';
			solong->info.coin--;
			solong->slime[solong->info.slime].is_free = 1;
		}
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
	if (!display_map(solong, &solong->window))
		exit((ft_clearall(solong), EXIT_FAILURE));
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
	solong->deco.index = 2;
	solong->random.rd_floor = get_randoms(0, 1, 2);
	solong->info.collectible = solong->info.coin;
	solong->player.animation = ft_calloc(9, sizeof(int));
	if (!solong->player.animation)
		return (0);
	solong->oeuil.animation = ft_calloc(3, sizeof(int));
	if (!solong->oeuil.animation)
		return (0);
	solong->slime = ft_calloc(solong->info.collectible, sizeof(t_slime));
	if (!solong->slime)
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
