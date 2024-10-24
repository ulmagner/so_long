/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:15:06 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:40:15 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	action_p(int button, int x, int y, t_all *all)
{
	if (button == 1)
	{
		all->attack.button = true;
		all->attack.curr_frame = 0;
		all->attack.tot_frame = 4;
		all->attack.x = x;
		all->attack.y = y;
	}
	else if (button == 3)
	{
		all->counter.button = true;
		all->counter.is_action = true;
		all->counter.curr_frame = 0;
		all->counter.tot_frame = 4;
		all->counter.x = x;
		all->counter.y = y;
		all->player.ms = 2;
	}
	return (0);
}

int	action_r(int button, int x, int y, t_all *all)
{
	int	i;

	(void) x;
	(void) y;
	i = -1;
	while (++i < 4 && !all->player.is_dead)
	{
		if (all->movement.i_move[i] == 1)
			all->player.i = i;
	}
	if (button == 1)
	{
		all->attack.button = false;
		all->attack.is_action = false;
	}
	if (button == 3)
	{
		all->counter.button = false;
		all->counter.curr_frame = 0;
		all->counter.is_action = false;
		all->player.ms = 4;
	}
	return (0);
}

static int	close_window(t_all *all)
{
	return (exit((ft_clearall(all), EXIT_FAILURE)), 0);
}

int	hook_handling(t_all *all)
{
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_hook(all->window.main, 17, 1L << 17, close_window, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}
