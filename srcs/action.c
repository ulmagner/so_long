/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/22 19:35:24 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	animation_attack(t_all *all, t_player *player)
{
	int	i;

	i = -1;
	if (all->movement.i_move[0] || all->movement.i_move[3])
		player->i = 4;
	else
		player->i = 5;
	if (all->attack.curr_frame == all->attack.tot_frame)
		all->attack.curr_frame = 0;
	if (all->attack.curr_frame <= all->attack.tot_frame)
	{
		player->animation[player->i] = all->attack.curr_frame;
		all->attack.curr_frame++;
	}
	while (++i < all->info.collectible)
	{
		if (all->dist.p_c[i] <= all->slime[i].r + player->r)
		{
			all->slime[i].c->is_visited = 2;
			all->slime[i].anim_slime = 1;
		}
	}
	return (1);
}

static int	animation_counter(t_all *all, t_player *player)
{
	player->i = 7;
	if (all->movement.i_move[0] || all->movement.i_move[3])
		player->i = 6;
	if (all->counter.curr_frame == all->counter.tot_frame)
		all->counter.curr_frame = 0;
	if (all->counter.curr_frame <= all->counter.tot_frame \
		&& all->counter.is_action)
	{
		player->animation[player->i] = all->counter.curr_frame;
		all->counter.curr_frame++;
	}
	return (1);
}

static int	attacking(t_all *all, t_player *player)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	animation_attack(all, player);
	while (++j < all->info.oeil)
	{
		i = -1;
		while (++i < all->info.ennemies)
		{
			if (all->dist.p_o[++k] <= all->oeil[j][i].r + player->r \
				&& all->oeil[j][i].is_stun)
			{
				all->oeil[j][i].i = 2;
				all->oeil[j][i].anim = 0;
				all->oeil[j][i].is_dead = true;
			}
		}
	}
	return (1);
}

static int	countering(t_all *all, t_player *player)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	all->counter.curr_frame_c++;
	animation_counter(all, player);
	while (++j < all->info.oeil)
	{
		i = -1;
		while (++i < all->info.ennemies)
			if (all->dist.p_o[++k] <= all->oeil[j][i].r + player->r)
				all->oeil[j][i].is_stun = true;
	}
	return (1);
}

void	action_handling(t_all *all, t_action *attack, t_action *counter)
{
	if (counter->button
		&& (counter->curr_frame_c <= counter->tot_frame_c) && !counter->reload)
		countering(all, &all->player);
	else if (counter->curr_frame_c > 0)
	{
		counter->reload = 1;
		if (counter->curr_frame_c-- <= 50)
			counter->reload = 0;
	}
	if (attack->button)
	{
		if (!attack->is_action && attack->curr_frame_c <= 80)
		{
			attack->curr_frame_c += 20;
			attack->is_action = 1;
		}
		if (((attack->curr_frame_c <= attack->tot_frame_c) && !attack->reload))
			attacking(all, &all->player);
	}
	else if (attack->curr_frame_c > 0)
	{
		attack->reload = 1;
		if (attack->curr_frame_c-- <= 50)
			attack->reload = 0;
	}
}
