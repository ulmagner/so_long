/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:58:41 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 16:57:59 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	burn_h(t_player *player, t_trap *trap, t_all *all, int i)
{
	if (all->dist.p_t[i] <= player->r + trap->r)
	{
		trap->tot_frame = 30;
		trap->detect = true;
	}
	else
		trap->detect = false;
	return (1);
}

int	trap_handling(t_all *all, t_trap *trap, int i)
{
	burn_h(&all->player, trap, all, i);
	if (trap->detect || trap->curr_frame < trap->tot_frame)
	{
		if (trap->curr_frame == trap->tot_frame)
			trap->curr_frame = 0;
		if (trap->curr_frame < trap->tot_frame)
		{
			if (all->i % 1000 == 0)
			{
				trap->anim_trap = (trap->anim_trap + 1) % 30;
				trap->curr_frame++;
			}
		}
		copy_trap_to_map(all, trap);
	}
	return (1);
}
