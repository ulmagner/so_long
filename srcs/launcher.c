/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:42:33 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:40:01 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	display_dynamique(t_all *all)
{
	int	i;

	int (j) = -1;
	int (k) = -1;
	while (++j < all->info.oeil)
	{
		i = -1;
		while (++i < all->info.ennemies)
		{
			k++;
			if (!all->player.is_dead)
				movement_handling_oeil(all, &all->oeil[j][i], k);
			if (all->dist.p_o[k] <= all->vision)
				copy_oeil_plan(all, &all->oeil[j][i]);
		}
	}
	slime_handling(all, all->slime);
	i = -1;
	while (++i < all->info.trap)
		trap_handling(all, &all->trap[i], i);
	if (all->info.coin == 0)
		all->info.exit = 1;
	copy_fog_plan(all);
	copy_player_plan(all);
	return (1);
}

static int	display_map(t_all *all, t_window *window)
{
	char *(step) = ft_itoa(all->step);
	build_plan(all);
	display_dynamique(all);
	copy_plan_to_game(all);
	copy_to_game(&all->tile[8][6][0], &all->game, 50, 600);
	copy_countdowns(&all->tile[8][6][1], &all->game,
		all->attack.curr_frame_c, 600);
	copy_to_game(&all->tile[8][6][0], &all->game, 50, 500);
	copy_countdowns(&all->tile[8][6][1], &all->game,
		all->counter.curr_frame_c, 500);
	if (all->movement.move[XK_m])
		build_minimap(all, all->tile, &all->game);
	if (all->player.is_dead)
		copy_to_view(&all->tile[8][0][0], &all->game, &all->view, all);
	if (mlx_put_image_to_window(window->mlx,
			window->main, all->game.img, 0, 0) < 0)
		return (0);
	if (mlx_string_put(all->window.mlx, all->window.main, \
		all->window.main_w / 2 - (all->view.x + all->view.w / 2) \
		+ all->player.x + 32, all->window.main_h / 2 \
		- (all->view.y + all->view.h / 2) + all->player.y \
		- 5, 0XFFFFFF, step) < 0)
		return (0);
	free(step);
	return (1);
}

int	looping(t_all *all)
{
	if (++(all->i) - all->frame < (int)(100 / 60))
		return (0);
	all->frame = all->i;
	ft_bzero(all->game.addr, \
		(all->game.w * all->game.h * all->game.bits_per_pixel / 8));
	if (mlx_clear_window(all->window.mlx, all->window.main) < 0)
		exit((ft_clearall(all), EXIT_FAILURE));
	calcul_dist(all);
	copy_ground_plan(all);
	set_view_to_ppos(&all->view, &all->player, all);
	if (!all->player.is_dead)
	{
		movement_handling(all);
		action_handling(all, &all->attack, &all->counter);
	}
	if (!display_map(all, &all->window))
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	launcher(t_all *all)
{
	if (!init_window(all))
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
	init_distances(all, &all->info);
	init_variables(all);
	if (!hook_handling(all))
		return (0);
	return (1);
}
