/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/07 14:08:34 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	attack_p(int button, int x, int y, t_solong *solong)
{
	solong->attack.attack[button] = true;
	solong->attack.is_attack = true;
	solong->attack.current_frame = 0;
	solong->attack.total_frame = 5;
	solong->attack.x = x;
	solong->attack.y = y;
	return (0);
}

int	attack_r(int button, int x, int y, t_solong *solong)
{
	int	i;

	(void) x;
	(void) y;
	i = -1;
	solong->attack.attack[button] = false;
	while (++i < 4)
	{
		if (solong->movement.index_move[i] == 1)
			solong->player.index = i;
	}
	solong->attack.current_frame = 0;
	solong->attack.is_attack = false;
	return (0);
}

int	attack_handling(t_solong *solong, t_player *player)
{
	if (solong->i % 20 != 0)
		return (0);
	if (solong->attack.attack[1])
	{
		if (solong->movement.index_move[0] || solong->movement.index_move[3])
			player->index = 4;
		else
			player->index = 5;
		if (solong->attack.current_frame < solong->attack.total_frame \
			&& solong->attack.is_attack)
		{
			player->animation[player->index] = solong->attack.current_frame;
			solong->attack.current_frame++;
		}
		if (solong->player.hero->index == 'C')
		{
			solong->player.hero->is_visited = 2;
			solong->deco.anim_jar = 1;
		}
	}
	return (1);
}

int	attack_handling(t_solong *solong, t_player *player)
{
	if (solong->i % 20 != 0)
		return (0);
	if (solong->attack.attack[3])
	{
		if (solong->movement.index_move[0] || solong->movement.index_move[3])
			player->index = 6;
		else
			player->index = 7;
		if (solong->attack.current_frame < solong->attack.total_frame \
			&& solong->attack.is_counter)
		{
			player->animation[player->index] = solong->attack.current_frame;
			solong->attack.current_frame++;
		}
		// if (solong->player.hero->index == 'C')
		// {
		// 	solong->player.hero->is_visited = 2;
		// 	solong->deco.anim_jar = 1;
		// }
	}
	return (1);
}
