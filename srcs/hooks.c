/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:15:06 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 14:41:24 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	action_p(int button, int x, int y, t_all *all)
{
	if (button == 1)
	{
		all->attack.button = true;
		all->attack.is_action = true;
		all->attack.curr_frame = 0;
		all->attack.tot_frame = 5;
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
		all->attack.curr_frame = 0;
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
