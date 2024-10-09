/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:57:23 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:49:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	free_the_slimes(t_all *all, t_slime *slime)
{
	if (all->player.h->is_visited == 2 \
		&& all->player.h->i == 'C')
	{
		if (!slime[all->info.slime].is_free)
			copy_to_map(&all->tileset[2][2][0], \
				&all->game, all->player.h);
		else
			all->info.slime++;
		if (all->movement.move[XK_e])
		{
			slime[all->info.slime].y = all->player.y;
			slime[all->info.slime].x = all->player.x;
			all->player.h->i = '0';
			all->info.coin--;
			slime[all->info.slime].is_free = true;
		}
	}
	return (1);
}

static int	move_slime(t_player player, t_slime *slime, int off_x, int off_y)
{
	if ((slime->y > player.y + off_y) && slime->y)
		slime->y -= player.ms;
	else if (slime->y < player.y + off_y)
		slime->y += player.ms;
	if (slime->x > player.x + off_x)
		slime->x -= player.ms;
	else if (slime->x < player.x + off_x)
		slime->x += player.ms;
	return (1);
}

int	slime_handling(t_all *all, t_slime *slime)
{
	int	i;

	i = -1;
	free_the_slimes(all, slime);
	while (++i < all->info.collectible && slime[i].is_free)
	{
		copy_slime_to_map(all, &slime[i]);
		if (all->i % 10000 == 0)
			slime[i].anim_slime = (slime[i].anim_slime + 1) % 5;
		if (all->movement.i_move[0])
			move_slime(all->player, &slime[i], 0, (32 + (i * 32)));
		else if (all->movement.i_move[1])
			move_slime(all->player, &slime[i], 0, (-32 - (i * 32)));
		if (all->movement.i_move[2])
			move_slime(all->player, &slime[i], (32 + (i * 32)), 0);
		else if (all->movement.i_move[3])
			move_slime(all->player, &slime[i], (-32 - (i * 32)), 0);
	}
	if (all->info.coin == 0)
		all->info.exit = 1;
	return (1);
}
