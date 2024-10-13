/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 22:49:13 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	copy_game_map(t_image *image, t_image *bg, t_all *all)
{
	unsigned int	color;
	int				x;
	int				y;

	(void) all;
	y = -1;
	while (++y < image->h)
	{
		x = -1;
		while (++x < image->w)
		{
			color = get_pixel_color(image, \
				0 * image->w + x, 0 * image->h + y);
			ft_pixel_put(bg, x + ((bg->w / 6) - (image->w / 6)), \
				y + ((bg->h / 6) - (image->h / 6)), color);
		}
	}
}

static int	display_map(t_all *all, t_window *window)
{
	int	i;

	i = -1;
	build_plan(all);
	while (++i < all->info.ennemies)
	{
		if (all->dist.p_o[i] <= 300.0f)
			copy_oeuil_to_map(all, &all->oeuil[i]);
	}
	i = -1;
	slime_handling(all, all->slime);
	copy_player_to_map(all);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i], i);
	copy_fog_map(all);
	if (all->player.is_dead)
		copy_plan_map(&all->tileset[8][0][0], &all->plan, all);
	copy_game_to_map(all);
	if (all->movement.move[XK_m])
		build_game(all);
	mlx_put_image_to_window(window->mlx,
		window->main, all->game.img, 0, 0);
	return (1);
}

static int	looping(t_all *all)
{
	int	i;

	i = -1;
	if (++(all->i) % 1500 != 0)
		return (0);
	calcul_dist(all);
	copy_ground_to_map(all);
	get_hitbox_player(&all->player);
	while (++i < all->info.ennemies)
	{
		if (!all->oeuil[i].is_dead && !all->oeuil[i].is_stun \
			&& !all->player.is_dead)
		{
			get_hitbox_oeuil(&all->oeuil[i]);
			movement_handling_oeuil(all, &all->oeuil[i], i);
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

int	launcher(t_all *all, char **av)
{
	init_window(all, av);
	if (!split_tileset(all, &all->info))
		return (0);
	init_bg(&all->ground, &all->plan, all, &all->window);
	init_game(&all->game, &all->window);
	all->deco.i = 2;
	all->random.rd_floor = get_randoms(0, 1, 2);
	all->info.collectible = all->info.coin;
	all->player.animation = ft_calloc(9, sizeof(int));
	if (!all->player.animation)
		return (0);
	build_ground(all);
	init_distances(all);
	all->player.ms = 4;
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
