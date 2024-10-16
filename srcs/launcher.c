/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 16:19:00 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_dynamique(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->info.ennemies)
		if (all->dist.p_o[i] <= 300.0f)
			copy_oeil_plan(all, &all->oeil[i]);
	slime_handling(all, all->slime);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i], i);
	return (1);
}

static int	display_map(t_all *all, t_window *window)
{
	char	*step;

	build_plan(all);
	display_dynamique(all);
	copy_fog_plan(all);
	copy_player_plan(all);
	copy_plan_to_game(all);
	if (all->movement.move[XK_m])
		build_minimap(all, all->tile, &all->game);
	if (all->player.is_dead)
		copy_to_view(&all->tile[8][0][0], &all->game, &all->view, all);
	if (mlx_put_image_to_window(window->mlx,
		window->main, all->game.img, 0, 0) < 0)
		return (0);
	step = ft_itoa(all->step);
	if (mlx_string_put(all->window.mlx, all->window.main, \
		all->window.main_w / 2 - (all->view.x + all->view.w / 2) \
		+ all->player.x + 32, all->window.main_h / 2 \
		- (all->view.y + all->view.h / 2) + all->player.y \
		- 5, 0XFFFFFF, step) < 0)
		return (0);
	free(step);
	return (1);
}

static int	looping(t_all *all)
{
	int	i;

	i = -1;
	if (++(all->i) - all->frame < (int)(10000 / 60))
		return (0);
	all->frame = all->i;
	ft_bzero(all->game.addr, (all->game.w * all->game.h * all->game.bits_per_pixel / 8));
	if (mlx_clear_window(all->window.mlx, all->window.main) < 0)
		exit((ft_clearall(all), EXIT_FAILURE));
	calcul_dist(all);
	copy_ground_plan(all);
	get_hitbox_player(&all->player);
	while (++i < all->info.ennemies)
	{
		if (!all->oeil[i].is_dead && !all->oeil[i].is_stun \
			&& !all->player.is_dead)
			movement_handling_oeil(all, &all->oeil[i], i);
	}
	set_view_to_ppos(&all->view, &all->player, all);
	if (!all->player.is_dead)
	{
		movement_handling(all);
		action_handling(all);
	}
	if (!display_map(all, &all->window))
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	hook_handling(t_all *all)
{
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}

int	launcher(t_all *all, char **av)
{
	if (!init_window(all, av))
		return (0);
	if (!split_tile(all, &all->info, &all->fail))
		return (0);
	if (!init_bg(&all->ground, &all->plan, all, &all->window))
		return (0);
	if (!init_game(&all->game, &all->window, all))
		return (0);
	init_view(all, &all->view);
	all->random.rd_floor = get_randoms(0, 1, 2);
	all->info.collectible = all->info.coin;
	all->player.animation = ft_calloc(9, sizeof(int));
	if (!all->player.animation)
		return (0);
	build_ground(all);
	init_distances(all);
	all->player.ms = 4;
	all->step = 0;
	all->i = -1;
	all->frame = 0;
	all->frameplayer = 0;
	if (!hook_handling(all))
		return (0);
	return (1);
}
