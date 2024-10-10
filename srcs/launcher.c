/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/10 17:07:37 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

float calculate_distance(t_player *player, float obj_x, float obj_y)
{
    return sqrt(pow(player->x - obj_x, 2) + pow(player->y - obj_y, 2));
}

int lerp_color(int color, t_color fog_color, float fog_factor)
{
    // Extract RGB components from the color (assuming it's in ARGB format)
	int a = (color >> 24) &  0xFF;
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    // Interpolate each channel
	a = (1.0f - fog_factor) * a + fog_factor * fog_color.a;
    r = (1.0f - fog_factor) * r + fog_factor * fog_color.r;
    g = (1.0f - fog_factor) * g + fog_factor * fog_color.g;
    b = (1.0f - fog_factor) * b + fog_factor * fog_color.b;

	if (a > 255) a = 255;
	if (a < 0) a = 0;
    // Repack into a single int (assuming no transparency is used)
    return (a << 24) | (r << 16) | (g << 8) | b;
}

int apply_fog(int color, t_all *all, t_color fog_color)
{
    float fog_factor;

	fog_factor = 0.0;
    if (all->fog.distance >= 100.0)
	{
		color = (color >> 1) & 8355711;
        if (all->fog.distance >= 300.0)
            fog_factor = 0.7;
        else
            fog_factor = (all->fog.distance - 100.0) / (300.0 - 100.0) - 0.3;
    	return lerp_color(color, fog_color, fog_factor);	
    }
	return (color);
}

void copy_fog_map(t_all *all)
{
    int	x;
	int	y;
    int original_color;
	int fogged_color;

	y = -1;
    while (++y < all->game.h)
	{
		x = -1;
        while (++x < all->game.w)
		{
            original_color = get_pixel_color(&all->game, x, y);
            all->fog.distance = calculate_distance(&all->player, x, y);
            fogged_color = apply_fog(original_color, all, all->argb);
            ft_pixel_put(&all->game, x, y, fogged_color);
        }
    }
}

static int	display_map(t_all *all, t_window *window)
{
	int	i;

	i = -1;
	build_game(all);
	while (++i < all->info.ennemies && calculate_distance(&all->player, all->oeuil[i].x, all->oeuil[i].y) < 300.0)
		copy_oeuil_to_map(all, &all->oeuil[i]);
	i = -1;
	slime_handling(all, all->slime);
	copy_player_to_map(all);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i]);
	copy_fog_map(all);
	if (all->player.is_dead)
		copy_game_map(&all->tileset[8][0][0], &all->game, all);
	mlx_put_image_to_window(window->mlx,
		window->main, all->game.img, \
		((all->window.main_w / 2) - ((all->info.column * 64) / 2)), \
		((all->window.main_h / 2) - ((all->info.line * 64) / 2)));
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

int	init_bg(t_image *ground, t_image *game, t_all *all, t_window *window)
{
	int	map_w_in_pixels;
	int	map_h_in_pixels;

	map_w_in_pixels = all->info.column * TILE_SIZE;
	map_h_in_pixels = all->info.line * TILE_SIZE;
	ground->w = map_w_in_pixels;
	ground->h = map_h_in_pixels;
	game->w = map_w_in_pixels;
	game->h = map_h_in_pixels;
	ground->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	ground->addr = mlx_get_data_addr(ground->img,
			&ground->bits_per_pixel,
			&ground->line_length, &ground->endian);
	game->img = mlx_new_image(window->mlx,
			map_w_in_pixels, map_h_in_pixels);
	game->addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel,
			&game->line_length, &game->endian);
	all->argb = (t_color){0, 0, 0, 0};
	return (1);
}

int	init_window(t_all *all, char **av)
{
	all->window.main_w = ft_atoi(av[2]);
	all->window.main_h = ft_atoi(av[3]) - 70;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_w, all->window.main_h, "So_long");
		return (1);
}

int	launcher(t_all *all, char **av)
{
	init_window(all, av);
	if (!split_tileset(all, &all->info))
		return (0);
	init_bg(&all->ground, &all->game, all, &all->window);
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
	copy_game_map(&all->tileset[8][0][0], &all->game, all);
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
