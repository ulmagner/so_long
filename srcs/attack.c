/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:23:08 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/02 18:27:48 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	attack_p(int button, int x, int y, t_solong *solong)
{
	solong->attack.attack[button] = true;
	solong->attack.current_frame = 0;
	solong->attack.total_frame = 5;
	solong->attack.x = x;
	solong->attack.y = y;
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
		if (solong->attack.current_frame < solong->attack.total_frame)
		{
			player->animation[4] = solong->attack.current_frame;
			solong->attack.current_frame++;
		}
		else
			solong->attack.current_frame = 0;
	}
	if (solong->attack.attack[3])
	{
		player->index = 5;
		if (solong->attack.current_frame < solong->attack.total_frame)
		{
			player->animation[5] = solong->attack.current_frame;
			solong->attack.current_frame++;
		}
		else
			solong->attack.current_frame = 0;
	}
	return (1);
}
