/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:57:23 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:04:56 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	free_the_slimes(t_solong *solong, t_slime *slime)
{
	if (solong->player.hero->is_visited == 2 && solong->player.hero->index == 'C')
	{
		if (!slime[solong->info.slime].is_free)
			copy_tile_to_map(&solong->tileset[2][2][0], &solong->game, solong->player.hero);
		else
			solong->info.slime++;
		if (solong->movement.move[XK_e])
		{
			slime[solong->info.slime].y = solong->player.y;
			slime[solong->info.slime].x = solong->player.x;
			solong->player.hero->index = '0';
			solong->info.coin--;
			slime[solong->info.slime].is_free = true;
		}
	}
	return (1);
}

static int	move_slime(t_player player, t_slime *slime, int off_x, int off_y)
{
	if ((slime->y > player.y + off_y) && slime->y )
		slime->y -= player.ms;
	else if (slime->y < player.y + off_y)
		slime->y += player.ms;
	if (slime->x > player.x + off_x)
		slime->x -= player.ms;
	else if (slime->x < player.x + off_x)
		slime->x += player.ms;
	return (1);
}

int	slime_handling(t_solong *solong, t_slime *slime)
{
	int	i;

	i = -1;
	free_the_slimes(solong, slime);
	while (++i < solong->info.collectible && slime[i].is_free)
	{
		copy_slime_to_map(solong, &slime[i]);
		if (solong->i % 10000 == 0)
			slime[i].anim_slime = (slime[i].anim_slime + 1) % 5;
		if (solong->movement.index_move[0])
			move_slime(solong->player, &slime[i], 0, (32 + (i * 32)));
		else if (solong->movement.index_move[1])
			move_slime(solong->player, &slime[i], 0, (-32 - (i * 32)));
		if (solong->movement.index_move[2])
			move_slime(solong->player, &slime[i], (32 + (i * 32)), 0);
		else if (solong->movement.index_move[3])
			move_slime(solong->player, &slime[i], (-32 - (i * 32)), 0);
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
	return (1);
}
