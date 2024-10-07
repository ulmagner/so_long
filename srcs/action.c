/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/07 17:04:58 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	action_p(int button, int x, int y, t_solong *solong)
{
	if (button == 1)
	{
		solong->attack.button = true;
		solong->attack.is_action = true;
		solong->attack.current_frame = 0;
		solong->attack.total_frame = 5;
		solong->attack.x = x;
		solong->attack.y = y;
	}
	else if (button == 3)
	{
		solong->counter.button = true;
		solong->counter.is_action = true;
		solong->counter.current_frame = 0;
		solong->counter.total_frame = 4;
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
	while (++i < 4)
	{
		if (solong->movement.index_move[i] == 1)
			solong->player.index = i;
	}
	if (button == 1)
	{
		solong->attack.button = false;
		solong->attack.current_frame = 0;
		solong->attack.is_action = false;
	}
	if (button == 3)
	{
		solong->counter.button = false;
		solong->counter.current_frame = 0;
		solong->counter.is_action = false;
	}
	return (0);
}

static int	attack(t_solong *solong, t_player *player)
{
	if (solong->movement.index_move[0] || solong->movement.index_move[3])
		player->index = 4;
	else
		player->index = 5;
	if (solong->counter.current_frame == solong->counter.total_frame)
		solong->counter.current_frame = 0;
	if (solong->attack.current_frame < solong->attack.total_frame \
		&& solong->attack.is_action)
	{
		player->animation[player->index] = solong->attack.current_frame;
		solong->attack.current_frame++;
	}
	if (solong->player.hero->index == 'C')
	{
		solong->player.hero->is_visited = 2;
		solong->deco.anim_jar = 1;
	}
	return (1);
}

static int	counter(t_solong *solong, t_player *player)
{
	if (solong->movement.index_move[0] || solong->movement.index_move[3])
		player->index = 6;
	else
		player->index = 7;
	if (solong->counter.current_frame == solong->counter.total_frame)
		solong->counter.current_frame = 0;
	if (solong->counter.current_frame < solong->counter.total_frame \
		&& solong->counter.is_action)
	{
		player->animation[player->index] = solong->counter.current_frame;
		solong->counter.current_frame++;
	}
	// if (solong->player.hero->index == 'C')
	// {
	// 	solong->player.hero->is_visited = 2;
	// 	solong->deco.anim_jar = 1;
	// }
	return (1);
}

int	action_handling(t_solong *solong)
{
	if (solong->i % 20 != 0)
		return (0);
	if (solong->counter.button)
		counter(solong, &solong->player);
	if (solong->attack.button)
		attack(solong, &solong->player);
	return (1);
}
