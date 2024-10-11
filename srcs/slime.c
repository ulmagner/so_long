/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:57:23 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 16:19:12 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	free_the_slimes(t_all *all, t_slime *slime)
{
	if (slime->c->is_visited == 2)
	{
		if (!slime->is_free)
			copy_to_map(&all->tileset[2][1][0], \
				&all->game, slime->c);
		if (all->movement.move[XK_e] && !slime->is_free)
		{
			slime->y = all->player.y;
			slime->x = all->player.x;
			all->info.coin--;
			slime->is_free = true;
			slime->i = 1;
			slime->c->is_visited = 3;
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
	while (++i < all->info.collectible)
	{
		free_the_slimes(all, &slime[i]);
		if (slime[i].is_free)
		{
			if (all->i % 1000 == 0)
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
		copy_slime_to_map(all, &slime[i]);
	}
	if (all->info.coin == 0)
		all->info.exit = 1;
	return (1);
}
