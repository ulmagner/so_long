/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:58:41 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 18:33:34 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	burn_hero(t_player *player, t_trap *trap)
{
	if (player->hero->right->down->index == 'F' || player->hero->left->down->index == 'F')
	{
		trap->x = player->hero->right->down->x_pxl;
		trap->y = player->hero->right->down->y_pxl;
		trap->tot_frame = 30;
		trap->detect = true;
	}
	else
		trap->detect = false;
	return (1);
}

int	trap_handling(t_solong *solong, t_trap *trap)
{
	burn_hero(&solong->player, trap);
	if (trap->detect || trap->curr_frame < trap->tot_frame)
	{
		if (trap->curr_frame == trap->tot_frame)
			trap->curr_frame = 0;
		if (trap->curr_frame < trap->tot_frame)
		{
			if (solong->i % 10000 == 0)
			{
				trap->anim_trap = (trap->anim_trap + 1) % 30;
				trap->curr_frame++;
			}
		}
		copy_trap_to_map(solong, trap);
	}
	return (1);
}
