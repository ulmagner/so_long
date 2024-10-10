/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/10 11:50:36 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	animation_attack(t_all *all, t_player *player)
{
	if (all->movement.i_move[0] || all->movement.i_move[3])
		player->i = 4;
	else
		player->i = 5;
	if (all->attack.curr_frame == all->attack.tot_frame)
		all->attack.curr_frame = 0;
	if (all->attack.curr_frame < all->attack.tot_frame \
		&& all->attack.is_action)
	{
		player->animation[player->i] = all->attack.curr_frame;
		all->attack.curr_frame++;
	}
	return (1);
}

static int	attack(t_all *all, t_player *player)
{
	int	i;

	i = -1;
	animation_attack(all, player);
	if (check_hitbox_jar(all->player.interaction, all->info))
	{
		all->player.h->is_visited = 2;
		all->deco.anim_jar = 1;
	}
	while (++i < all->info.ennemies)
	{
		if (check_hitbox_oeuil(all->player.interaction, &all->oeuil[i]) \
			&& all->oeuil[i].is_stun)
		{
			all->oeuil[i].i = 2;
			all->oeuil[i].anim = 0;
			all->oeuil[i].is_dead = true;
		}
	}
	return (1);
}

static int	counter(t_all *all, t_player *player)
{
	int	i;

	i = -1;
	if (all->movement.i_move[0] || all->movement.i_move[3])
		player->i = 6;
	else
		player->i = 7;
	if (all->counter.curr_frame == all->counter.tot_frame)
		all->counter.curr_frame = 0;
	if (all->counter.curr_frame < all->counter.tot_frame \
		&& all->counter.is_action)
	{
		player->animation[player->i] = all->counter.curr_frame;
		all->counter.curr_frame++;
	}
	while (++i < all->info.ennemies)
	{
		if (check_hitbox_oeuil(all->player.interaction, &all->oeuil[i]))
			all->oeuil[i].is_stun = true;
	}
	return (1);
}

int	action_handling(t_all *all)
{
	if (all->counter.button)
		counter(all, &all->player);
	if (all->attack.button)
		attack(all, &all->player);
	return (1);
}
