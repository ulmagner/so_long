/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/09 17:55:25 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	action_p(int button, int x, int y, t_solong *solong)
{
	if (button == 1)
	{
		solong->attack.button = true;
		solong->attack.is_action = true;
		solong->attack.curr_frame = 0;
		solong->attack.tot_frame = 5;
		solong->attack.x = x;
		solong->attack.y = y;
	}
	else if (button == 3)
	{
		solong->counter.button = true;
		solong->counter.is_action = true;
		solong->counter.curr_frame = 0;
		solong->counter.tot_frame = 4;
		solong->counter.x = x;
		solong->counter.y = y;
	}
	return (0);
}

int	action_r(int button, int x, int y, t_solong *solong)
{
	int	i;

	(void) x;
	(void) y;
	i = -1;
	while (++i < 4 && !solong->player.is_dead)
	{
		if (solong->movement.index_move[i] == 1)
			solong->player.index = i;
	}
	if (button == 1)
	{
		solong->attack.button = false;
		solong->attack.curr_frame = 0;
		solong->attack.is_action = false;
	}
	if (button == 3)
	{
		solong->counter.button = false;
		solong->counter.curr_frame = 0;
		solong->counter.is_action = false;
	}
	return (0);
}

int	check_hitbox_oeuil(int interaction[4][2], t_oeuil *oeuil)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	while (++i < 4)
	{
		x = interaction[i][0];
		y = interaction[i][1];
		if (x >= oeuil->x && x <= oeuil->x + 64 \
			&& y >= oeuil->y && y <= oeuil->y + 64)
			return (1);
	}
	return (0);
}

int	check_hitbox_jar(int interaction[4][2], t_info info)
{
	int	x;
	int	y;
	int	i;
	int	j;

	j = -1;
	while (++j < info.collectible)
	{
		i = -1;
		while (++i < 4)
		{
			x = interaction[i][0];
			y = interaction[i][1];
			if (x >= info.deco[j][0] && x <= info.deco[j][0] + 64 \
				&& y >= info.deco[j][1] && y <= info.deco[j][1] + 64)
				return (1);
		}
	}
	return (0);
}

static int	attack(t_solong *solong, t_player *player)
{
	int	i;
	
	i = -1;
	if (solong->movement.index_move[0] || solong->movement.index_move[3])
		player->index = 4;
	else
		player->index = 5;
	if (solong->counter.curr_frame == solong->counter.tot_frame)
		solong->counter.curr_frame = 0;
	if (solong->attack.curr_frame < solong->attack.tot_frame \
		&& solong->attack.is_action)
	{
		player->animation[player->index] = solong->attack.curr_frame;
		solong->attack.curr_frame++;
	}
	if (check_hitbox_jar(solong->player.interaction, solong->info))
	{
		solong->player.hero->is_visited = 2;
		solong->deco.anim_jar = 1;
	}
	while (++i < solong->info.ennemies)
	{
		if (check_hitbox_oeuil(solong->player.interaction, &solong->oeuil[i]) && solong->oeuil[i].is_stun)
		{
			solong->oeuil[i].index = 2;
			solong->oeuil[i].anim = 0;
			solong->oeuil[i].is_dead = true;
		}
	}
	return (1);
}

static int	counter(t_solong *solong, t_player *player)
{
	int	i;

	i = -1;
	if (solong->movement.index_move[0] || solong->movement.index_move[3])
		player->index = 6;
	else
		player->index = 7;
	if (solong->counter.curr_frame == solong->counter.tot_frame)
		solong->counter.curr_frame = 0;
	if (solong->counter.curr_frame < solong->counter.tot_frame \
		&& solong->counter.is_action)
	{
		player->animation[player->index] = solong->counter.curr_frame;
		solong->counter.curr_frame++;
	}
	while (++i < solong->info.ennemies)
	{
		if (check_hitbox_oeuil(solong->player.interaction, &solong->oeuil[i]))
			solong->oeuil[i].is_stun = true;
	}
	return (1);
}

int	action_handling(t_solong *solong)
{
	if (solong->counter.button)
		counter(solong, &solong->player);
	if (solong->attack.button)
		attack(solong, &solong->player);
	return (1);
}
