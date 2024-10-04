/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/04 15:26:45 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	movement_p(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (0);
}

void	check_mouvment(t_player *player)
{
	if (player->animation[player->index] != 0)
		player->animation[player->index] = 0;
}

int	movement_r(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = false;
	check_mouvment(&solong->player);
	return (0);
}

int	movement_handling(t_solong *solong)
{
	if (solong->i % 10 != 0)
		return (0);
	solong->player.ms = 8;
	if (!solong->attack.is_attack)
	{
		dir_up(&solong->player, &solong->movement, solong);
		dir_down(&solong->player, &solong->movement, solong);
		dir_left(&solong->player, &solong->movement, solong);
		dir_right(&solong->player, &solong->movement, solong);
	}
	if (solong->player.hero->index == 'E' && solong->info.exit \
		&& solong->movement.move[XK_e])
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (1);
}
