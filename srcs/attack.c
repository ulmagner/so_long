/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/03 23:22:50 by ulysse           ###   ########.fr       */
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
	solong->attack.frame_c = 0;
	solong->attack.frame_delay = 10;
	return (0);
}

int	attack_r(int button, int x, int y, t_solong *solong)
{
	(void) x;
	(void) y;
	solong->attack.attack[button] = false;
	return (0);
}

int	attack_handling(t_solong *solong, t_player *player)
{
	if (solong->attack.attack[1])
	{
		player->index = 4;
		if (solong->attack.frame_c++ >= solong->attack.frame_delay)
		{
			if (solong->attack.current_frame < solong->attack.total_frame && solong->attack.is_attack)
			{
				player->animation[4] = solong->attack.current_frame;
				solong->attack.current_frame++;
			}
			else
			{
				player->index = 1;
				solong->attack.current_frame = 0;
				solong->attack.is_attack = false;
			}
			solong->attack.frame_c = 0;
			if (solong->player.hero->index == 'C')
				solong->player.hero->is_visited = 2;
		}
	}
	if (solong->attack.attack[3])
	{
		player->index = 5;
		if (solong->attack.current_frame < solong->attack.total_frame && solong->attack.is_attack)
		{
			player->animation[5] = solong->attack.current_frame;
			solong->attack.current_frame++;
		}
		else
		{
			player->index = 1;
			solong->attack.current_frame = 0;
			solong->attack.is_attack = false;
		}
	}
	return (1);
}
