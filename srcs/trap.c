/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:58:41 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	burn_h(t_player *player, t_trap *trap)
{
	if (player->h->right->down->i == 'F' \
		|| player->h->left->down->i == 'F')
	{
		trap->x = player->h->right->down->x_pxl;
		trap->y = player->h->right->down->y_pxl;
		trap->tot_frame = 30;
		trap->detect = true;
	}
	else
		trap->detect = false;
	return (1);
}

int	trap_handling(t_all *all, t_trap *trap)
{
	burn_h(&all->player, trap);
	if (trap->detect || trap->curr_frame < trap->tot_frame)
	{
		if (trap->curr_frame == trap->tot_frame)
			trap->curr_frame = 0;
		if (trap->curr_frame < trap->tot_frame)
		{
			if (all->i % 10000 == 0)
			{
				trap->anim_trap = (trap->anim_trap + 1) % 30;
				trap->curr_frame++;
			}
		}
		copy_trap_to_map(all, trap);
	}
	return (1);
}
